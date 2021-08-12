local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/atmosphere", table.unpack(arg));
cs("src/atmosphere_frag", table.unpack(arg));
