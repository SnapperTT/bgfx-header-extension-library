local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/lum", arg[1], arg[2], arg[3]);
cs("src/lum_avg", "-vdef", "lum", arg[1], arg[2], arg[3]);
cs("src/lum_avg", "-o", "lum_avg_output", "-vdef", "lum", "-D", "MULTIFRAME_AVERAGED", arg[1], arg[2], arg[3]);

