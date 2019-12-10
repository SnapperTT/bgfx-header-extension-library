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
// u_blurParameters[i].x = weight[i+1], u_blurParameters[i].y = offset[i+1]
// weight[0] is in u_blurParameters[0].z;
// offset[0] is by definition 0
// nLookups is in u_blurParameters[0].w;
uniform vec4 u_blurParameters[8];	

void main() {
	// Guassian blurs in each axis
	int nLookups = int(u_blurParameters[0].w);
	float weight0 = u_blurParameters[0].z;

	vec3 rgb = texture2D(s_texColor, v_texcoord0).xyz * weight0;
    vec2 tex_offset = 1.0 / u_screenSize.xy; // gets size of single texel

	for (int i = 0; i < nLookups; ++i) {
		#ifdef BLUR_HZ
			rgb += texture2D(s_texColor, v_texcoord0 + vec2(tex_offset.x * u_blurParameters[i].y, 0.0)).rgb * u_blurParameters[i].x;
			rgb += texture2D(s_texColor, v_texcoord0 - vec2(tex_offset.x * u_blurParameters[i].y, 0.0)).rgb * u_blurParameters[i].x;
		#endif

		#ifdef BLUR_VT
			rgb += texture2D(s_texColor, v_texcoord0 + vec2(0.0, tex_offset.y * u_blurParameters[i].y)).rgb * u_blurParameters[i].x;
			rgb += texture2D(s_texColor, v_texcoord0 - vec2(0.0, tex_offset.y * u_blurParameters[i].y)).rgb * u_blurParameters[i].x;
		#endif
		}

	gl_FragColor = vec4(rgb, 1.0);
	}

