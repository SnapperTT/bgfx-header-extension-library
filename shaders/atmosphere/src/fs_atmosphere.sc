$input v_normal, v_tangent, v_bitangent
// Implementation of Sean O'Neil's atmospheric shader
// Used for skyFromGround and skyFromSpace

#include <bgfx_shader.shh>
#include <shader_lib.shh>
#include <atmospheric_functions.shh>

// Uniforms
uniform vec4 u_sunDirection; // Normalised direction to the sun
uniform vec4 u_atmosphericParams[2]; 	// u_atmosphericParams[0] -> xyz = tint color, w = sun intensity.
//----------------------------------	// u_atmosphericParams[1] -> xyz = rayleigh parameters (for non-earth atmospheres), w = "g" phase parameter.

void main() {
	float fG = u_atmosphericParams[1].w; // g scattering parameter
	float g2 = fG*fG;
	
	float fCos = dot(u_sunDirection.xyz, v_bitangent)/length(v_bitangent);
	float fCos2 = fCos * fCos;
	vec3 color = getRayleighPhase(fCos2) * v_normal +
		         getMiePhase(fCos, fCos2, fG, g2) * v_tangent;
		         
	color = vec3_splat(1.0) - exp(-color);
	color = toGamma(toAcesFilmic(color));
	gl_FragColor = vec4(color.rgb, max(color.b, color.r));
	}


