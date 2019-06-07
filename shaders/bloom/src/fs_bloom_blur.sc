$input v_texcoord0
#include <bgfx_shader.shh>

// Samplers
SAMPLER2D(s_texColor,  0);

uniform vec4 u_screenSize;

// Doing more taps is cheaper than doing more passes
// Here I'm using interpolated offsets and weights to leverage the GPU's
// linear interpolated lookup of textures, using the formula described at:
// rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/

// Blurring constants
#define KERNAL_SIZE 5
#define bloomOffsetR bloomOffset5
#define bloomWeightR bloomWeight5

void main() {
	// Guassian blurs in each axis
	
// Array definition must be in the function body to make HLSL happy

//const ARRAY_BEGIN(float, bloomOffset3, 3) 0.0, 1.3846153846, 3.2307692308 ARRAY_END();
//const ARRAY_BEGIN(float, bloomWeight3, 3) 0.2270270270, 0.3162162162, 0.0702702703 ARRAY_END(); // 9 tap with 5 lookups

const ARRAY_BEGIN(float, bloomOffset5, 5) 0.0, 1.4444444444, 3.3703703704, 5.2962962963, 7.2222222222 ARRAY_END(); 
const ARRAY_BEGIN(float, bloomWeight5, 5) 0.1550637538, 0.2591779886, 0.1257775533, 0.0330993561, 0.0044132475 ARRAY_END();//17 tap with 9 lookups

	vec3 rgb = 1.0*texture2D(s_texColor, v_texcoord0).xyz * bloomWeightR[0];
    vec2 tex_offset = 1.0 / u_screenSize.xy; // gets size of single texel

	for(int i = 1; i < KERNAL_SIZE; ++i) {
		#ifdef BLUR_HZ
			rgb += texture2D(s_texColor, v_texcoord0 + vec2(tex_offset.x * bloomOffsetR[i], 0.0)).rgb * bloomWeightR[i];
			rgb += texture2D(s_texColor, v_texcoord0 - vec2(tex_offset.x * bloomOffsetR[i], 0.0)).rgb * bloomWeightR[i];
		#endif

		#ifdef BLUR_VT
			rgb += texture2D(s_texColor, v_texcoord0 + vec2(0.0, tex_offset.y * bloomOffsetR[i])).rgb * bloomWeightR[i];
			rgb += texture2D(s_texColor, v_texcoord0 - vec2(0.0, tex_offset.y * bloomOffsetR[i])).rgb * bloomWeightR[i];
		#endif
		}

	gl_FragColor = vec4(rgb, 1.0);
	}

