
#include <bgfx_shader.shh>

void main() {
	#ifdef USE_VSM
		// For variance shadow mapping - write depth and depth^2 to colour buffer
		gl_FragColor = vec4(gl_FragCoord.z, gl_FragCoord.z*gl_FragCoord.z, 0.0, 1.0);
	#else
		gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	#endif
	}


