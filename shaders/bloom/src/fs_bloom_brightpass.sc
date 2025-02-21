$input v_texcoord0
#include <bgfx_shader.shh>

// Samplers
SAMPLER2D(s_texColor,  0);

#ifdef USE_LUM
	SAMPLER2D(s_texLum, 1);
	
	float getExposure(float lum) {
		return 0.3 + 0.7/clamp(lum + 0.5, 0.1, 1.0);
		}
#endif

void main() {
	// Extracts the bright pixels for bloom calculation	
	vec3 rgb = texture2D(s_texColor, v_texcoord0).xyz; // Scene linear colour
	
	#ifdef USE_LUM
		float lum = texture2D(s_texLum, vec2(0.5,0.5)).r; // Already averaged Lum, from the LumFilter
		float exposure = getExposure(lum); // Overexpose bright areas in dark scenes
		rgb *= exposure;
	#else
		// In order to see any bloom you must set some rgb pixels to be greater than 1.0
		// This will require floating point framebuffers (eg bgfx::TextureFormat::RGBA16F)
		// Or you can multiply rgb by some value here
	#endif

	// By convention, we want any pixels with any element > 1.0 to "bloom".
	// This is so that red light sources, etc bloom
	float lumaBloom = max(max(max(rgb.r, rgb.g), rgb.b) - 1.0, 0.0);
	gl_FragColor = vec4(max(vec3_splat(0.0), lumaBloom * normalize(rgb)), 1.0);
	}
