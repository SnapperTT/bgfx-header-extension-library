$input v_normal, v_tangent

// Implementation of Sean O'Neil's atmospheric shader
// See atmospheric_functions.shh for more details

#include <bgfx_shader.shh>
#include <shader_lib.shh>
#include <atmospheric_functions.shh> 

// Uniforms
uniform vec4 u_sunDirection; 		// Sun vector in world. Normaised direction to it.
uniform vec4 u_worldPosAndSize; 	// The position and size of the world being rendered. (x,y,z) = position of the world in model space, w = world radius
uniform vec4 u_atmosphericParams[2]; 	// u_atmosphericParams[0] -> xyz = tint color, w = sun intensity.
//----------------------------------	// u_atmosphericParams[1] -> xyz = rayleigh parameters (for non-earth atmospheres), w = "g" phase parameter.

void main() {
	float fInnerRadius = u_worldPosAndSize.w;     		// The inner (planetary) radius
	float fOuterRadius = (1.0/DRADIUS) * fInnerRadius;	// The outer (atmosphere) radius
	float fESun = u_atmosphericParams[0].w; 		// The strength of the sun
	vec3 v3MieTint = u_atmosphericParams[0].xyz; 	// The color of the mie scattering particles
	vec3 v3RayleighTint = u_atmosphericParams[1].xyz; // Used for non-earth atmospheres
	float fG = u_atmosphericParams[1].w; 			// g scattering parameter
	
	vec3 v3Origin = v_normal.xyz; // The position of this relative to the camera
	vec3 v3Pos = v_tangent.xyz; // vertex position. Here we're projecting a unit sphere coordinate to a planet's surface
	vec3 v3LightDir = -u_sunDirection.xyz; // normalized vector to the light source, not the light position
	
	// Renormalise position
	vec3 v3Normal = (v3Pos - v3Origin);
	v3Normal = normalize(v3Normal);
	v3Pos = fOuterRadius*v3Normal + v3Origin;

	// Do the scattering calcs
	vec3 v3RayleighColor;
	vec3 v3MieColor;
	vec3 v3PosOut;
	atmosphereSky (fInnerRadius, fOuterRadius, v3Pos, v3Origin, v3LightDir, v3RayleighTint, v3MieTint, v3RayleighColor, v3MieColor, v3PosOut);

	// Finally, scale the Mie and Rayleigh colors
	v3RayleighColor = v3RayleighColor * fESun;
	v3MieColor = v3MieColor * fESun;
	v3PosOut = v3PosOut;
	
	const float g = -0.98;
	const float g2 = g*g;
	float fCos = dot(u_sunDirection.xyz, v3PosOut)/length(v3PosOut);
	float fCos2 = fCos * fCos;
	vec3 color = getRayleighPhase(fCos2) * v3RayleighColor +
		         getMiePhase(fCos, fCos2, g, g2) * v3MieColor;

	color = vec3_splat(1.0) - exp(-color);
	color = toGamma(toAcesFilmic(color));
	gl_FragColor = vec4(color.rgb, 1.0);
	}

