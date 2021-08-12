local cs = loadfile("compile_shaders.lua") or loadfile("../compile_shaders.lua"); 
cs("src/tonemapping", table.unpack(arg));
cs("src/tonemapping", "-o", "src/tonemapping_ch1", "-D", "TM_1_CHANNEL", table.unpack(arg));
cs("src/tonemapping", "-o", "src/tonemapping_ch2", "-D", "TM_1_CHANNEL", "-D", "TM_2_CHANNEL", table.unpack(arg));
cs("src/tonemapping", "-o", "src/tonemapping_ch3", "-D", "TM_1_CHANNEL", "-D", "TM_2_CHANNEL", "-D", "TM_3_CHANNEL", table.unpack(arg));
cs("src/tonemapping", "-o", "src/tonemapping_ch4", "-D", "TM_1_CHANNEL", "-D", "TM_2_CHANNEL", "-D", "TM_3_CHANNEL", "-D", "TM_4_CHANNEL", table.unpack(arg));
