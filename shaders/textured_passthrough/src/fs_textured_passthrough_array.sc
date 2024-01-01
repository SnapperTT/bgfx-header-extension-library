$input v_texcoord0

// Include the bgfx shader library here
// Various parts of this uber shader are adopted from bgfx, and are therefore
// under the following license, henceforth refered to "bgfx licnese".
/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
#include <bgfx_shader.shh>

// Samplers
SAMPLER2DARRAY(s_texColor,  0);
uniform vec4 u_bgfxhUtilUniform;

void  main() {
	vec4 tex = texture2DArray(s_texColor, vec3(v_texcoord0, u_bgfxhUtilUniform[0]));
	gl_FragColor = tex;
	}

