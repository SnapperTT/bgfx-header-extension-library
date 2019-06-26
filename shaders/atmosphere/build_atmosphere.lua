local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua");
cs("src/atmosphere", arg[1], arg[2], arg[3]);
cs("src/atmosphere_frag", arg[1], arg[2], arg[3]);
