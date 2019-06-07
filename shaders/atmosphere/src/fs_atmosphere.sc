$input v_normal, v_tangent, v_bitangent
// Implementation of Sean O'Neil's atmospheric shader

#include <bgfx_shader.shh>


// Uniforms
uniform vec4 u_sunDirection; // Normalised direction to the sun

float getMiePhase(float fCos, float fCos2, float g, float g2) {
   return 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);
	}
 
float getRayleighPhase(float fCos2) {
   return 0.75 * (2.0 + 0.5 * fCos2);
	}

void main() {
	const float g = -0.98;
	const float g2 = g*g;
	float fCos = dot(u_sunDirection.xyz, v_bitangent)/length(v_bitangent);
	float fCos2 = fCos * fCos;
	vec3 color = getRayleighPhase(fCos2) * v_normal +
		         getMiePhase(fCos, fCos2, g, g2) * v_tangent;

	gl_FragColor = vec4(color.rgb, color.b);
	}


