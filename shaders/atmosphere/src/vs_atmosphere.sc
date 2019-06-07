$input a_position
$output v_normal, v_tangent, v_bitangent

// Implementation of Sean O'Neil's atmospheric shader
// Handles SkyFromSpace and SkyFromGround scenarios
// To use:
// 		1. Set uniforms 
//		2. Render a unit sphere at the planet's origin (for a "flat" planet render the sphere at (cameraX, -radius, cameraZ), radius=6371e3)
// TODO: Remove unit sphere stuff, that is seriously dumb

#include <bgfx_shader.shh>

// Uniforms
uniform vec4 u_sunDirection; 		// Sun vector in world. Normaised direction to it.
uniform vec4 u_eyePosition;  		// Position of the camera relative to world
uniform vec4 u_worldPosAndSize; 	// The position and size of the world being rendered. (x,y,z) = position of the world in model space, w = world radius
uniform vec4 u_cameraOffset;		// == u_eyePosition.xyz - u_worldPosAndSize.xyz. Seperate uniform to prevent floating point resolution issues for very large planets

#define SCALE_DEPTH 0.25

float atmosphereScale(float fCos) {
	float x = 1.0 - fCos;
	return SCALE_DEPTH * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
	}

float getNearIntersection(vec3 pos, vec3 ray, float distance2, float radius2) {
	float B = 2.0 * dot(pos, ray);
	float C = distance2 - radius2;
	float det = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B - sqrt(det));
	}

void main() {
	// Assumes the skydome is a unit sphere centered on the "centre" of the world
	#ifndef PI
		#define PI 3.14159265359
	#endif
	#define ATMOMUL 1.0e-2

	float fWorldRadius = u_worldPosAndSize.w;
	float fDrawRadius = (1.0/0.975) * fWorldRadius; // The atmosphere should be ~2.5% the thickness of the planet for best results

	const float fBetaMieMultiplier = 0.25*ATMOMUL;
	const float fBetaRayleighMultiplier = 0.20*ATMOMUL;
	const float fESun = 10.0; // Solar intensity

	const float wavelengthRed = 0.650; // in nm
	const float wavelengthGreen = 0.570;
	const float wavelengthBlue = 0.475;

	const vec3 v3InvWavelength = vec3(1.0 / pow(wavelengthRed, 4), 1.0 / pow(wavelengthGreen, 4), 1.0 / pow(wavelengthBlue, 4)); // 1 / pow(wavelength, 4) for RGB. Elements evaluate to roughly 5.0-20.0

	float fOuterRadius = fDrawRadius;//1.025;     // The outer (atmosphere) radius
	float fOuterRadius2 = fOuterRadius*fOuterRadius;    // fOuterRadius^2

	float fInnerRadius = fWorldRadius;     // The inner (planetary) radius
	float fInnerRadius2 = fInnerRadius*fInnerRadius;    // fInnerRadius^2

	const float fKrESun = fBetaRayleighMultiplier * fESun;     // Kr * ESun
	const float fKmESun = fBetaMieMultiplier * fESun;          // Km * ESun
	const float fKr4PI = fBetaRayleighMultiplier * 4 * PI;     // Kr * 4 * PI
	const float fKm4PI = fBetaMieMultiplier * 4 * PI;          // Km * 4 * PI

	float fScale = 1.0 / (fOuterRadius - fInnerRadius);           // 1 / (fOuterRadius - fInnerRadius)
	float fScaleOverScaleDepth = fScale / SCALE_DEPTH; // fScale / fScaleDepth
	const int nSamples = 4;
	const float fSamples = nSamples;
	const float fInvSamples = 1.0/fSamples;

	const float fInvScaleDepth = 1.0 / SCALE_DEPTH;


	// Get the ray from the camera to the vertex and its length (which
	// is the far point of the ray passing through the atmosphere)
	vec3 cameraOffset = u_cameraOffset.xyz;
	//0*vec3(0,fInnerRadius, 0);

	vec3 v3CameraPos = (u_eyePosition.xyz) + cameraOffset;//vec3(0.0, fInnerRadius, 0.0);
	vec3 v3LightDir = -u_sunDirection.xyz; // normalized vector to the light source, not the light position
	float fCameraHeight = length(v3CameraPos);    // The camera's current height
	float fCameraHeight2 = fCameraHeight*fCameraHeight;   // fCameraHeight^2


	vec3 v3Pos = a_position.xyz * fOuterRadius;// fOuterRadius; // vertex position
	vec3 v3Ray = v3Pos - v3CameraPos;
	float fFar = length(v3Ray);
	v3Ray /= fFar;

	vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
	bool isSkyFromSpace = fCameraHeight > fOuterRadius;

	if (isSkyFromSpace) {
		// Calculate the closest intersection of the ray with
		// the outer atmosphere (point A in Figure 16-3)
		float fNear = getNearIntersection(v3CameraPos, v3Ray, fCameraHeight2,
				                        fOuterRadius2);

		// Calculate the ray's start and end positions in the atmosphere,
		// then calculate its scattering offset
		vec3 v3Start = v3CameraPos + v3Ray * fNear;
		fFar -= fNear;
		float fStartAngle = dot(v3Ray, v3Start) / fOuterRadius;
		float fStartDepth = exp(-fInvScaleDepth);
		float fStartOffset = fStartDepth * atmosphereScale(fStartAngle);

		// Initialize the scattering loop variables
		float fSampleLength = fFar / fSamples;
		float fScaledLength = fSampleLength * fScale;
		vec3 v3SampleRay = v3Ray * fSampleLength;
		vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;

		// Now loop through the sample points
		for(int i=0; i<nSamples; i++) {
			float fHeight = length(v3SamplePoint);
			float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
			float fLightAngle = dot(v3LightDir, v3SamplePoint) / fHeight;
			float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
			float fScatter = (fStartOffset + fDepth * (atmosphereScale(fLightAngle) - atmosphereScale(fCameraAngle)));
			vec3 v3Attenuate = exp(-fScatter *
						             (v3InvWavelength * fKr4PI + fKm4PI));
			v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
			v3SamplePoint += v3SampleRay;
			}
		}
	else {
		// Calculate the ray's starting position, then calculate its scattering offset
		vec3 v3Start = v3CameraPos;
		float fHeight = length(v3Start);
		float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fCameraHeight));
		float fStartAngle = dot(v3Ray, v3Start) / fHeight;
		float fStartOffset = fDepth*atmosphereScale(fStartAngle);

		// Initialize the scattering loop variables
		float fSampleLength = fFar * fInvSamples;	
		float fScaledLength = fSampleLength * fScale;
		vec3 v3SampleRay = v3Ray * fSampleLength;
		vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;

		// Now loop through the sample rays
		for(int i=0; i<nSamples; i++) {
			fHeight = length(v3SamplePoint);
			fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
			float fLightAngle = dot(v3LightDir, v3SamplePoint) / fHeight;
			float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
			float fScatter = (fStartOffset + fDepth*(atmosphereScale(fLightAngle) - atmosphereScale(fCameraAngle)));
			vec3 v3Attenuate = exp(-fScatter *
									(v3InvWavelength * fKr4PI + fKm4PI));
			v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
			v3SamplePoint += v3SampleRay;
			}
		}

	// Error handling
	//if (isNan(v3FrontColor)) {
	//	v3FrontColor = vec3(1,0,0);
	//	}
	v3FrontColor = max(v3FrontColor, vec3_splat(0.0));

	float dRadius = fDrawRadius;
	//if (u_frametime.w > 0.5) {
	//	// inner sphere hack. Used for debugging the skydome
	//	dRadius = fInnerRadius;
	//	}

	// Finally, scale the Mie and Rayleigh colors
	v_normal = v3FrontColor * (v3InvWavelength * fKrESun);
	v_tangent = v3FrontColor * fKmESun;
	v_bitangent = v3CameraPos - v3Pos;
	//gl_Position = mul(u_modelViewProj, vec4(a_position*dRadius - cameraOffset, 1.0) );
	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0) );
	}



