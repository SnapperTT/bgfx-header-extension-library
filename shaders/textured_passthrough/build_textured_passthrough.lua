local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/textured_passthrough", table.unpack(arg));
cs("src/untextured_passthrough", "-vdef", "textured_passthrough", table.unpack(arg));
cs("src/textured_passthrough_monochromatic", "-vdef", "textured_passthrough", table.unpack(arg));
cs("src/textured_passthrough_array", "-vdef", "textured_passthrough", table.unpack(arg));
