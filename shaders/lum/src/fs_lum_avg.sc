$input v_texcoord0
/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
#include <bgfx_shader.shh>
#include <shader_lib.shh>

// Samplers
SAMPLER2D(s_texColor,  0);

#ifdef MULTIFRAME_AVERAGED
	SAMPLER2D(s_texLum,    1);
	// Uniforms
	uniform vec4 u_frametime;    // u_frametime.x = frametime, u_frametime.y = framecount
#endif
uniform vec4 u_offset[16];

void main() {
// Computes average lum from 16 samples
// Adapted from bgfx example 09-HDR under the bgfx license
/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
	float sum;
	sum  = (texture2D(s_texColor, v_texcoord0+u_offset[ 0].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[ 1].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[ 2].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[ 3].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[ 4].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[ 5].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[ 6].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[ 7].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[ 8].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[ 9].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[10].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[11].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[12].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[13].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[14].xy) ).r;
	sum += (texture2D(s_texColor, v_texcoord0+u_offset[15].xy) ).r;
	float avg = sum/16.0;

	#ifdef MULTIFRAME_AVERAGED
		float lum = texture2D(s_texLum, vec2(0.5,0.5)).r; // Already averaged Lum from previous frame
		float d = u_frametime.x; // The frametime as reported by  
		gl_FragColor = vec4(avg*d + lum*(1.0-d), 0.0, 0.0, 1.0);
	#else
		gl_FragColor = vec4(avg, 0.0, 0.0, 1.0);
	#endif
	}


