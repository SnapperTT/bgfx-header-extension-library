$input v_texcoord0
/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
#include <bgfx_shader.shh>
#include <shader_lib.shh>

// Samplers
SAMPLER2D(s_texColor,  0);

// Uniforms
uniform vec4 u_offset[16];

float luma2(vec3 rgb) {
	return luma(rgb).x;
	}

void main() {
// Computes average lum from 9 samples
// Adapted from bgfx example 09-HDR under the bgfx license
/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
	// textures are in linear space
	vec3 rgb0 = (texture2D(s_texColor, v_texcoord0+u_offset[0].xy) ).xyz;
	vec3 rgb1 = (texture2D(s_texColor, v_texcoord0+u_offset[1].xy) ).xyz;
	vec3 rgb2 = (texture2D(s_texColor, v_texcoord0+u_offset[2].xy) ).xyz;
	vec3 rgb3 = (texture2D(s_texColor, v_texcoord0+u_offset[3].xy) ).xyz;
	vec3 rgb4 = (texture2D(s_texColor, v_texcoord0+u_offset[4].xy) ).xyz;
	vec3 rgb5 = (texture2D(s_texColor, v_texcoord0+u_offset[5].xy) ).xyz;
	vec3 rgb6 = (texture2D(s_texColor, v_texcoord0+u_offset[6].xy) ).xyz;
	vec3 rgb7 = (texture2D(s_texColor, v_texcoord0+u_offset[7].xy) ).xyz;
	vec3 rgb8 = (texture2D(s_texColor, v_texcoord0+u_offset[8].xy) ).xyz;
	float avg = luma2(rgb0)
			  + luma2(rgb1)
			  + luma2(rgb2)
			  + luma2(rgb3)
			  + luma2(rgb4)
			  + luma2(rgb5)
			  + luma2(rgb6)
			  + luma2(rgb7)
			  + luma2(rgb8)
			  ;
	avg *= 1.0/9.0;

	gl_FragColor = vec4(avg, 0.0, 0.0, 1.0);
	}


