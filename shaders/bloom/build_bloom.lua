local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/bloom_brightpass", "-o", "bloom_brightpass", "-vdef", "bloom", table.unpack(arg));
cs("src/bloom_brightpass", "-o", "bloom_brightpass_lum", "-vdef", "bloom", "-D", "USE_LUM", table.unpack(arg));
cs("src/bloom_blur", "-o", "bloom_blur_hz", "-vdef", "bloom", "-D", "BLUR_HZ", table.unpack(arg));
cs("src/bloom_blur", "-o", "bloom_blur_vt", "-vdef", "bloom", "-D", "BLUR_VT", table.unpack(arg));


