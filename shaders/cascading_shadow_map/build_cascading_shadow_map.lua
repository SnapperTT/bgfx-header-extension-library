local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/cascading_shadow_map", arg[1], arg[2], arg[3]);
cs("src/cascading_shadow_map", "-o", "cascading_shadow_map_vsm", "-D", "USE_VSM", arg[1], arg[2], arg[3]);

