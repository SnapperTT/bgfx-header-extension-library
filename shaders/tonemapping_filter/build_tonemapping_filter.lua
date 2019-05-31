local cs = loadfile("../compile_shaders.lua");
cs("src/tonemapping", arg[1], arg[2], arg[3]);
cs("src/tonemapping", "-o", "src/tonemapping_ch1", "-D", "TM_1_CHANNEL", arg[1], arg[2], arg[3]);
cs("src/tonemapping", "-o", "src/tonemapping_ch2", "-D", "TM_1_CHANNEL", "-D", "TM_2_CHANNEL", arg[1], arg[2], arg[3]);
cs("src/tonemapping", "-o", "src/tonemapping_ch3", "-D", "TM_1_CHANNEL", "-D", "TM_2_CHANNEL", "-D", "TM_3_CHANNEL", arg[1], arg[2], arg[3]);
cs("src/tonemapping", "-o", "src/tonemapping_ch4", "-D", "TM_1_CHANNEL", "-D", "TM_2_CHANNEL", "-D", "TM_3_CHANNEL", "-D", "TM_4_CHANNEL", arg[1], arg[2], arg[3]);
