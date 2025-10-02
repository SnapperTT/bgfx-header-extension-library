$input v_texcoord0

// Include the bgfx shader library here
// Various parts of this uber shader are adopted from bgfx, and are therefore
// under the following license, henceforth refered to "bgfx licnese".
/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
#include <bgfx_shader.shh>
#include <shader_lib.shh>

// Samplers
SAMPLER2D(s_texColor,  0);
SAMPLER2D(s_texLum,  1);

#ifdef TM_1_CHANNEL
	SAMPLER2D(s_texFilterExtra0,  2);
#endif
#ifdef TM_2_CHANNEL
	SAMPLER2D(s_texFilterExtra1,  3);
#endif
#ifdef TM_3_CHANNEL
	SAMPLER2D(s_texFilterExtra2,  4);
#endif
#ifdef TM_4_CHANNEL
	SAMPLER2D(s_texFilterExtra3,  5);
#endif

uniform vec4 u_weightsAdd;
uniform vec4 u_weightsMul;

float getExposure(vec3 rgb, float lum) {
	return 0.3 + 0.7/clamp(lum + 0.5, 0.5, 1.0);
	}

void  main() {
	vec4 tex = texture2D(s_texColor, v_texcoord0);
	float lum = texture2D(s_texLum, v_texcoord0).r;
	
	// Blend additional samplers
	#ifdef TM_1_CHANNEL
	if (u_weightsAdd.x > 0.0) { // Addative
		vec3 texAdd = texture2D(s_texFilterExtra0, v_texcoord0).rgb;
		tex.rgb += texAdd*u_weightsAdd.x;
		}
	else if (u_weightsMul.x > 0.0) { // Multiplicitive
		float texMul = texture2D(s_texFilterExtra0, v_texcoord0).r;
		tex.xyz *= u_weightsMul.x*texMul + (1.0-u_weightsMul.x);
		}
	#endif
		
	#ifdef TM_2_CHANNEL
	if (u_weightsAdd.y > 0.0) {
		vec3 texAdd = texture2D(s_texFilterExtra1, v_texcoord0).rgb;
		tex.rgb += texAdd*u_weightsAdd.y;
		}
	else if (u_weightsMul.y > 0.0) {
		float texMul = texture2D(s_texFilterExtra1, v_texcoord0).r;
		tex.xyz *= u_weightsMul.y*texMul + (1.0-u_weightsMul.y);
		}
	#endif
		
	#ifdef TM_3_CHANNEL
	if (u_weightsAdd.z > 0.0) {
		vec3 texAdd = texture2D(s_texFilterExtra2, v_texcoord0).rgb;
		tex.rgb += texAdd*u_weightsAdd.z;
		}
	else if (u_weightsMul.z > 0.0) {
		float texMul = texture2D(s_texFilterExtra2, v_texcoord0).r;
		tex.xyz *= u_weightsMul.z*texMul + (1.0-u_weightsMul.z);
		}
	#endif
	
	#ifdef TM_4_CHANNEL
	if (u_weightsAdd.w > 0.0) {
		vec3 texAdd = texture2D(s_texFilterExtra3, v_texcoord0).rgb;
		tex.rgb += texAdd*u_weightsAdd.w;
		}
	else if (u_weightsMul.w > 0.0) {
		float texMul = texture2D(s_texFilterExtra3, v_texcoord0).r;
		tex.xyz *= u_weightsMul.w*texMul + (1.0-u_weightsMul.w);
		}
	#endif
	
	float exposure = getExposure(tex.rgb, lum);
	tex.rgb = toGamma(toAcesFilmic(tex.rgb * exposure));
	gl_FragColor = tex;
	}

