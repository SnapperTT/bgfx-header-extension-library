local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/guassian_blur", "-o", "guassian_blur_hz", "-vdef", "guassian_blur", "-D", "BLUR_HZ", table.unpack(arg));
cs("src/guassian_blur", "-o", "guassian_blur_vt", "-vdef", "guassian_blur", "-D", "BLUR_VT", table.unpack(arg));


