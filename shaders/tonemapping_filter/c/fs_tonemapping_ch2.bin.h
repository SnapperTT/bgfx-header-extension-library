static const uint8_t fs_tonemapping_ch2_bin_glsl[] = {
  0x46, 0x53, 0x48, 0x06, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x0a, 0x73,  // FSH.o.><.......s
  0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x08,  // _texColor.......
  0x73, 0x5f, 0x74, 0x65, 0x78, 0x4c, 0x75, 0x6d, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x11, 0x73,  // s_texLum.......s
  0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x30,  // _texFilterExtra0
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x11, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74,  // .......s_texFilt
  0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x31, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x0c, 0x75,  // erExtra1.......u
  0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64, 0x64, 0x02, 0x01, 0x00, 0x00, 0x01,  // _weightsAdd.....
  0x00, 0x0c, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x02, 0x01,  // ..u_weightsMul..
  0x00, 0x00, 0x01, 0x00, 0x35, 0x05, 0x00, 0x00, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20,  // ....5...varying 
  0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30,  // vec2 v_texcoord0
  0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65,  // ;.uniform sample
  0x72, 0x32, 0x44, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3b, 0x0a,  // r2D s_texColor;.
  0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32,  // uniform sampler2
  0x44, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x4c, 0x75, 0x6d, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66,  // D s_texLum;.unif
  0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x73, 0x5f,  // orm sampler2D s_
  0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x30, 0x3b,  // texFilterExtra0;
  0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72,  // .uniform sampler
  0x32, 0x44, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78,  // 2D s_texFilterEx
  0x74, 0x72, 0x61, 0x31, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x76, 0x65,  // tra1;.uniform ve
  0x63, 0x34, 0x20, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64, 0x64, 0x3b,  // c4 u_weightsAdd;
  0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x75, 0x5f,  // .uniform vec4 u_
  0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64,  // weightsMul;.void
  0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x76, 0x65, 0x63,  //  main ().{.  vec
  0x34, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20,  // 4 tex_1;.  vec4 
  0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76,  // tmpvar_2;.  tmpv
  0x61, 0x72, 0x5f, 0x32, 0x20, 0x3d, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44,  // ar_2 = texture2D
  0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2c, 0x20, 0x76, 0x5f,  //  (s_texColor, v_
  0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x65,  // texcoord0);.  te
  0x78, 0x5f, 0x31, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a,  // x_1 = tmpvar_2;.
  0x20, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x3b,  //   vec4 tmpvar_3;
  0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x74, 0x65,  // .  tmpvar_3 = te
  0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x4c, 0x75,  // xture2D (s_texLu
  0x6d, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x3b,  // m, v_texcoord0);
  0x0a, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74,  // .  if ((u_weight
  0x73, 0x41, 0x64, 0x64, 0x2e, 0x78, 0x20, 0x3e, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x20, 0x7b,  // sAdd.x > 0.0)) {
  0x0a, 0x20, 0x20, 0x20, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d,  // .    tex_1.xyz =
  0x20, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2b,  //  (tmpvar_2.xyz +
  0x20, 0x28, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73, 0x5f, 0x74,  //  (texture2D (s_t
  0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x30, 0x2c, 0x20,  // exFilterExtra0, 
  0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x2e, 0x78, 0x79, 0x7a,  // v_texcoord0).xyz
  0x20, 0x2a, 0x20, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64, 0x64, 0x2e,  //  * u_weightsAdd.
  0x78, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x7d, 0x20, 0x65, 0x6c, 0x73, 0x65, 0x20, 0x7b, 0x0a,  // x));.  } else {.
  0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68,  //     if ((u_weigh
  0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x78, 0x20, 0x3e, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x20,  // tsMul.x > 0.0)) 
  0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79,  // {.      tex_1.xy
  0x7a, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2a,  // z = (tex_1.xyz *
  0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e,  //  ((u_weightsMul.
  0x78, 0x20, 0x2a, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73,  // x * texture2D (s
  0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x30,  // _texFilterExtra0
  0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x2e, 0x78,  // , v_texcoord0).x
  0x29, 0x20, 0x2b, 0x20, 0x28, 0x31, 0x2e, 0x30, 0x20, 0x2d, 0x20, 0x75, 0x5f, 0x77, 0x65, 0x69,  // ) + (1.0 - u_wei
  0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x78, 0x29, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20,  // ghtsMul.x)));.  
  0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28,  //   };.  };.  if (
  0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64, 0x64, 0x2e, 0x79, 0x20,  // (u_weightsAdd.y 
  0x3e, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x74, 0x65,  // > 0.0)) {.    te
  0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x65, 0x78, 0x5f, 0x31,  // x_1.xyz = (tex_1
  0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2b, 0x20, 0x28, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32,  // .xyz + (texture2
  0x44, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78,  // D (s_texFilterEx
  0x74, 0x72, 0x61, 0x31, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64,  // tra1, v_texcoord
  0x30, 0x29, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2a, 0x20, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68,  // 0).xyz * u_weigh
  0x74, 0x73, 0x41, 0x64, 0x64, 0x2e, 0x79, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x7d, 0x20, 0x65,  // tsAdd.y));.  } e
  0x6c, 0x73, 0x65, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x28, 0x75,  // lse {.    if ((u
  0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x79, 0x20, 0x3e, 0x20,  // _weightsMul.y > 
  0x30, 0x2e, 0x30, 0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x65,  // 0.0)) {.      te
  0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x65, 0x78, 0x5f, 0x31,  // x_1.xyz = (tex_1
  0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2a, 0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68,  // .xyz * ((u_weigh
  0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x79, 0x20, 0x2a, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72,  // tsMul.y * textur
  0x65, 0x32, 0x44, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72,  // e2D (s_texFilter
  0x45, 0x78, 0x74, 0x72, 0x61, 0x31, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f,  // Extra1, v_texcoo
  0x72, 0x64, 0x30, 0x29, 0x2e, 0x78, 0x29, 0x20, 0x2b, 0x20, 0x28, 0x31, 0x2e, 0x30, 0x20, 0x2d,  // rd0).x) + (1.0 -
  0x20, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x79, 0x29,  //  u_weightsMul.y)
  0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x7d, 0x3b, 0x0a,  // ));.    };.  };.
  0x20, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x5f, 0x72, 0x67, 0x62, 0x5f, 0x34, 0x3b, 0x0a, 0x20,  //   vec3 _rgb_4;. 
  0x20, 0x5f, 0x72, 0x67, 0x62, 0x5f, 0x34, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x65, 0x78, 0x5f, 0x31,  //  _rgb_4 = (tex_1
  0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2a, 0x20, 0x28, 0x30, 0x2e, 0x33, 0x20, 0x2b, 0x20, 0x28, 0x30,  // .xyz * (0.3 + (0
  0x2e, 0x37, 0x20, 0x2f, 0x20, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x63, 0x6c, 0x61, 0x6d, 0x70, 0x20,  // .7 / .    clamp 
  0x28, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x2e, 0x78, 0x20, 0x2b, 0x20, 0x30,  // ((tmpvar_3.x + 0
  0x2e, 0x32, 0x29, 0x2c, 0x20, 0x30, 0x2e, 0x31, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x0a, 0x20,  // .2), 0.1, 1.0). 
  0x20, 0x29, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79,  //  )));.  tex_1.xy
  0x7a, 0x20, 0x3d, 0x20, 0x70, 0x6f, 0x77, 0x20, 0x28, 0x61, 0x62, 0x73, 0x28, 0x63, 0x6c, 0x61,  // z = pow (abs(cla
  0x6d, 0x70, 0x20, 0x28, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x5f, 0x72, 0x67, 0x62, 0x5f,  // mp (.    ((_rgb_
  0x34, 0x20, 0x2a, 0x20, 0x28, 0x28, 0x32, 0x2e, 0x35, 0x31, 0x20, 0x2a, 0x20, 0x5f, 0x72, 0x67,  // 4 * ((2.51 * _rg
  0x62, 0x5f, 0x34, 0x29, 0x20, 0x2b, 0x20, 0x30, 0x2e, 0x30, 0x33, 0x29, 0x29, 0x20, 0x2f, 0x20,  // b_4) + 0.03)) / 
  0x28, 0x28, 0x5f, 0x72, 0x67, 0x62, 0x5f, 0x34, 0x20, 0x2a, 0x20, 0x28, 0x0a, 0x20, 0x20, 0x20,  // ((_rgb_4 * (.   
  0x20, 0x20, 0x20, 0x28, 0x32, 0x2e, 0x34, 0x33, 0x20, 0x2a, 0x20, 0x5f, 0x72, 0x67, 0x62, 0x5f,  //    (2.43 * _rgb_
  0x34, 0x29, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x20, 0x30, 0x2e, 0x35, 0x39, 0x29, 0x29,  // 4).     + 0.59))
  0x20, 0x2b, 0x20, 0x30, 0x2e, 0x31, 0x34, 0x29, 0x29, 0x0a, 0x20, 0x20, 0x2c, 0x20, 0x30, 0x2e,  //  + 0.14)).  , 0.
  0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x29, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x33, 0x28, 0x30,  // 0, 1.0)), vec3(0
  0x2e, 0x34, 0x35, 0x34, 0x35, 0x34, 0x35, 0x34, 0x2c, 0x20, 0x30, 0x2e, 0x34, 0x35, 0x34, 0x35,  // .4545454, 0.4545
  0x34, 0x35, 0x34, 0x2c, 0x20, 0x30, 0x2e, 0x34, 0x35, 0x34, 0x35, 0x34, 0x35, 0x34, 0x29, 0x29,  // 454, 0.4545454))
  0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72,  // ;.  gl_FragColor
  0x20, 0x3d, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00 };            // or = tex_1;.}...
unsigned int fs_tonemapping_ch2_bin_glsl_size = 1470;

BX_UNUSED(fs_tonemapping_ch2_bin_glsl)
BX_UNUSED(fs_tonemapping_ch2_bin_glsl_size)
static const uint8_t * fs_tonemapping_ch2_bin_dx9 = NULL;
unsigned int fs_tonemapping_ch2_bin_dx9_size = 0;

BX_UNUSED(fs_tonemapping_ch2_bin_dx9)
BX_UNUSED(fs_tonemapping_ch2_bin_dx9_size)
static const uint8_t * fs_tonemapping_ch2_bin_dx11 = NULL;
unsigned int fs_tonemapping_ch2_bin_dx11_size = 0;

BX_UNUSED(fs_tonemapping_ch2_bin_dx11)
BX_UNUSED(fs_tonemapping_ch2_bin_dx11_size)
static const uint8_t * fs_tonemapping_ch2_bin_metal = NULL;
unsigned int fs_tonemapping_ch2_bin_metal_size = 0;

BX_UNUSED(fs_tonemapping_ch2_bin_metal)
BX_UNUSED(fs_tonemapping_ch2_bin_metal_size)
static const uint8_t * fs_tonemapping_ch2_bin_spirv = NULL;
unsigned int fs_tonemapping_ch2_bin_spirv_size = 0;

BX_UNUSED(fs_tonemapping_ch2_bin_spirv)
BX_UNUSED(fs_tonemapping_ch2_bin_spirv_size)
static const uint8_t * fs_tonemapping_ch2_bin_esslandroid = NULL;
unsigned int fs_tonemapping_ch2_bin_esslandroid_size = 0;

BX_UNUSED(fs_tonemapping_ch2_bin_esslandroid)
BX_UNUSED(fs_tonemapping_ch2_bin_esslandroid_size)
static const uint8_t * fs_tonemapping_ch2_bin_pssl = NULL;
unsigned int fs_tonemapping_ch2_bin_pssl_size = 0;

BX_UNUSED(fs_tonemapping_ch2_bin_pssl)
BX_UNUSED(fs_tonemapping_ch2_bin_pssl_size)
static const uint8_t * fs_tonemapping_ch2_bin_esslnacl = NULL;
unsigned int fs_tonemapping_ch2_bin_esslnacl_size = 0;

BX_UNUSED(fs_tonemapping_ch2_bin_esslnacl)
BX_UNUSED(fs_tonemapping_ch2_bin_esslnacl_size)
