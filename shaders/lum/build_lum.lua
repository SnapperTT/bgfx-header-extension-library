local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/lum", table.unpack(arg));
cs("src/lum_avg", "-vdef", "lum", table.unpack(arg));
cs("src/lum_avg", "-o", "lum_avg_output", "-vdef", "lum", "-D", "MULTIFRAME_AVERAGED", table.unpack(arg));

