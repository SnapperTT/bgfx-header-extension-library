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
SAMPLER2D(s_texColor,  0);

void  main() {
	float tex = texture2D(s_texColor, v_texcoord0).r;
	gl_FragColor = vec4(tex, tex, tex, 1.0);
	}

