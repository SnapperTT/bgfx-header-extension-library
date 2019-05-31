local cs = loadfile("../compile_shaders.lua");
cs("src/bloom_brightpass", "-o", "bloom_brightpass", arg[1], arg[2], arg[3]);
cs("src/bloom_brightpass", "-o", "bloom_brightpass_lum", "-D", "USE_LUM", arg[1], arg[2], arg[3]);
cs("src/bloom_blur", "-o", "bloom_blur_hz", "-D", "BLUR_HZ", arg[1], arg[2], arg[3]);
cs("src/bloom_blur", "-o", "bloom_blur_vt", "-D", "BLUR_VT", arg[1], arg[2], arg[3]);


