$input a_position
$output v_normal, v_tangent, v_bitangent

// Implementation of Sean O'Neil's atmospheric shader
// See atmospheric_functions.shh for more details

#include <bgfx_shader.shh>
#include <atmospheric_functions.shh> 

// Uniforms
uniform vec4 u_sunDirection; 		// Sun vector in world. Normaised direction to it.
uniform vec4 u_worldPosAndSize; 	// The position and size of the world being rendered. (x,y,z) = position of the world in model space, w = world radius
uniform vec4 u_atmosphericParams[2]; 	// u_atmosphericParams[0] -> xyz = tint color, w = sun intensity.
//----------------------------------	// u_atmosphericParams[1] -> xyz = rayleigh parameters (for non-earth atmospheres), w = "g" phase parameter.

void main() {
	// Assumes the skydome is a unit sphere centered on the "centre" of the world
	float fInnerRadius = u_worldPosAndSize.w;     		// The inner (planetary) radius
	float fOuterRadius = (1.0/DRADIUS) * fInnerRadius;	// The outer (atmosphere) radius
	float fESun = u_atmosphericParams[0].w; 		// The strength of the sun
	vec3 v3MieTint = u_atmosphericParams[0].xyz; 	// The color of the mie scattering particles
	vec3 v3RayleighTint = u_atmosphericParams[1].xyz; // Used for non-earth atmospheres
	float fG = u_atmosphericParams[1].w; 			// g scattering parameter
	
	vec3 v3Origin = mul(u_modelView, vec4(0.0,0.0,0.0,1.0)).xyz; // The position of this relative to the camera
	vec3 v3Pos = mul(u_modelView, vec4(a_position.xyz * fOuterRadius, 1.0)).xyz; // vertex position. Here we're projecting a unit sphere coordinate to a planet's surface
	vec3 v3LightDir = -u_sunDirection.xyz; // normalized vector to the light source, not the light position

	vec3 v3RayleighColor;
	vec3 v3MieColor;
	vec3 v3PosOut;
	atmosphereSky (fInnerRadius, fOuterRadius, v3Pos, v3Origin, v3LightDir, v3RayleighTint, v3MieTint, v3RayleighColor, v3MieColor, v3PosOut);

	// Finally, scale the Mie and Rayleigh colors
	v_normal = v3RayleighColor * fESun;
	v_tangent = v3MieColor * fESun;
	v_bitangent = v3PosOut;
	gl_Position = mul(u_modelViewProj, vec4(a_position*fOuterRadius, 1.0) ); 
	}



