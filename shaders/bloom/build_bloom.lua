local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/bloom_brightpass", "-o", "bloom_brightpass", "-vdef", "bloom", arg[1], arg[2], arg[3]);
cs("src/bloom_brightpass", "-o", "bloom_brightpass_lum", "-vdef", "bloom", "-D", "USE_LUM", arg[1], arg[2], arg[3]);
cs("src/bloom_blur", "-o", "bloom_blur_hz", "-vdef", "bloom", "-D", "BLUR_HZ", arg[1], arg[2], arg[3]);
cs("src/bloom_blur", "-o", "bloom_blur_vt", "-vdef", "bloom", "-D", "BLUR_VT", arg[1], arg[2], arg[3]);


