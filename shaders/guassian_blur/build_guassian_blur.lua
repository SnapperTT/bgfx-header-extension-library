local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/guassian_blur", "-o", "guassian_blur_hz", "-vdef", "guassian_blur", "-D", "BLUR_HZ", arg[1], arg[2], arg[3]);
cs("src/guassian_blur", "-o", "guassian_blur_vt", "-vdef", "guassian_blur", "-D", "BLUR_VT", arg[1], arg[2], arg[3]);


