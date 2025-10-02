local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/cascading_shadow_map", table.unpack(arg));
cs("src/cascading_shadow_map", "-o", "cascading_shadow_map_vsm", "-D", "USE_VSM", table.unpack(arg));

