static const uint8_t fs_tonemapping_ch3_bin_glsl[] = {
  0x46, 0x53, 0x48, 0x06, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x0a, 0x73,  // FSH.o.><.......s
  0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x08,  // _texColor.......
  0x73, 0x5f, 0x74, 0x65, 0x78, 0x4c, 0x75, 0x6d, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x11, 0x73,  // s_texLum.......s
  0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x30,  // _texFilterExtra0
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x11, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74,  // .......s_texFilt
  0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x31, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x11, 0x73,  // erExtra1.......s
  0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x32,  // _texFilterExtra2
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x0c, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73,  // .......u_weights
  0x41, 0x64, 0x64, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x0c, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67,  // Add.......u_weig
  0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x90, 0x06, 0x00, 0x00,  // htsMul..........
  0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x5f, 0x74,  // varying vec2 v_t
  0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72,  // excoord0;.unifor
  0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x73, 0x5f, 0x74, 0x65,  // m sampler2D s_te
  0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20,  // xColor;.uniform 
  0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x4c,  // sampler2D s_texL
  0x75, 0x6d, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70,  // um;.uniform samp
  0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65,  // ler2D s_texFilte
  0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d,  // rExtra0;.uniform
  0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78,  //  sampler2D s_tex
  0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x31, 0x3b, 0x0a, 0x75, 0x6e,  // FilterExtra1;.un
  0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20,  // iform sampler2D 
  0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61,  // s_texFilterExtra
  0x32, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20,  // 2;.uniform vec4 
  0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64, 0x64, 0x3b, 0x0a, 0x75, 0x6e,  // u_weightsAdd;.un
  0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x75, 0x5f, 0x77, 0x65, 0x69,  // iform vec4 u_wei
  0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61,  // ghtsMul;.void ma
  0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74,  // in ().{.  vec4 t
  0x65, 0x78, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70,  // ex_1;.  vec4 tmp
  0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f,  // var_2;.  tmpvar_
  0x32, 0x20, 0x3d, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73,  // 2 = texture2D (s
  0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78,  // _texColor, v_tex
  0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31,  // coord0);.  tex_1
  0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x76,  //  = tmpvar_2;.  v
  0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x3b, 0x0a, 0x20, 0x20,  // ec4 tmpvar_3;.  
  0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75,  // tmpvar_3 = textu
  0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x4c, 0x75, 0x6d, 0x2c, 0x20,  // re2D (s_texLum, 
  0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x3b, 0x0a, 0x20, 0x20,  // v_texcoord0);.  
  0x69, 0x66, 0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64,  // if ((u_weightsAd
  0x64, 0x2e, 0x78, 0x20, 0x3e, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20,  // d.x > 0.0)) {.  
  0x20, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x28, 0x74,  //   tex_1.xyz = (t
  0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2b, 0x20, 0x28, 0x74,  // mpvar_2.xyz + (t
  0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46,  // exture2D (s_texF
  0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x30, 0x2c, 0x20, 0x76, 0x5f, 0x74,  // ilterExtra0, v_t
  0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2a, 0x20,  // excoord0).xyz * 
  0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64, 0x64, 0x2e, 0x78, 0x29, 0x29,  // u_weightsAdd.x))
  0x3b, 0x0a, 0x20, 0x20, 0x7d, 0x20, 0x65, 0x6c, 0x73, 0x65, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20,  // ;.  } else {.   
  0x20, 0x69, 0x66, 0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d,  //  if ((u_weightsM
  0x75, 0x6c, 0x2e, 0x78, 0x20, 0x3e, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20,  // ul.x > 0.0)) {. 
  0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d,  //      tex_1.xyz =
  0x20, 0x28, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2a, 0x20, 0x28, 0x28,  //  (tex_1.xyz * ((
  0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x78, 0x20, 0x2a,  // u_weightsMul.x *
  0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65,  //  texture2D (s_te
  0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x30, 0x2c, 0x20, 0x76,  // xFilterExtra0, v
  0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x2e, 0x78, 0x29, 0x20, 0x2b,  // _texcoord0).x) +
  0x20, 0x28, 0x31, 0x2e, 0x30, 0x20, 0x2d, 0x20, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74,  //  (1.0 - u_weight
  0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x78, 0x29, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d,  // sMul.x)));.    }
  0x3b, 0x0a, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x28, 0x75, 0x5f,  // ;.  };.  if ((u_
  0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64, 0x64, 0x2e, 0x79, 0x20, 0x3e, 0x20, 0x30,  // weightsAdd.y > 0
  0x2e, 0x30, 0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31,  // .0)) {.    tex_1
  0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79,  // .xyz = (tex_1.xy
  0x7a, 0x20, 0x2b, 0x20, 0x28, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28,  // z + (texture2D (
  0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61,  // s_texFilterExtra
  0x31, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x2e,  // 1, v_texcoord0).
  0x78, 0x79, 0x7a, 0x20, 0x2a, 0x20, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41,  // xyz * u_weightsA
  0x64, 0x64, 0x2e, 0x79, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x7d, 0x20, 0x65, 0x6c, 0x73, 0x65,  // dd.y));.  } else
  0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65,  //  {.    if ((u_we
  0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x79, 0x20, 0x3e, 0x20, 0x30, 0x2e, 0x30,  // ightsMul.y > 0.0
  0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31,  // )) {.      tex_1
  0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79,  // .xyz = (tex_1.xy
  0x7a, 0x20, 0x2a, 0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d,  // z * ((u_weightsM
  0x75, 0x6c, 0x2e, 0x79, 0x20, 0x2a, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44,  // ul.y * texture2D
  0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x45, 0x78, 0x74,  //  (s_texFilterExt
  0x72, 0x61, 0x31, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30,  // ra1, v_texcoord0
  0x29, 0x2e, 0x78, 0x29, 0x20, 0x2b, 0x20, 0x28, 0x31, 0x2e, 0x30, 0x20, 0x2d, 0x20, 0x75, 0x5f,  // ).x) + (1.0 - u_
  0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x79, 0x29, 0x29, 0x29, 0x3b,  // weightsMul.y)));
  0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x69,  // .    };.  };.  i
  0x66, 0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64, 0x64,  // f ((u_weightsAdd
  0x2e, 0x7a, 0x20, 0x3e, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20,  // .z > 0.0)) {.   
  0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x65,  //  tex_1.xyz = (te
  0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2b, 0x20, 0x28, 0x74, 0x65, 0x78, 0x74, 0x75,  // x_1.xyz + (textu
  0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c, 0x74, 0x65,  // re2D (s_texFilte
  0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x32, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f,  // rExtra2, v_texco
  0x6f, 0x72, 0x64, 0x30, 0x29, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2a, 0x20, 0x75, 0x5f, 0x77, 0x65,  // ord0).xyz * u_we
  0x69, 0x67, 0x68, 0x74, 0x73, 0x41, 0x64, 0x64, 0x2e, 0x7a, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20,  // ightsAdd.z));.  
  0x7d, 0x20, 0x65, 0x6c, 0x73, 0x65, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x69, 0x66, 0x20,  // } else {.    if 
  0x28, 0x28, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x7a,  // ((u_weightsMul.z
  0x20, 0x3e, 0x20, 0x30, 0x2e, 0x30, 0x29, 0x29, 0x20, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,  //  > 0.0)) {.     
  0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x65,  //  tex_1.xyz = (te
  0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2a, 0x20, 0x28, 0x28, 0x75, 0x5f, 0x77, 0x65,  // x_1.xyz * ((u_we
  0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c, 0x2e, 0x7a, 0x20, 0x2a, 0x20, 0x74, 0x65, 0x78,  // ightsMul.z * tex
  0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x46, 0x69, 0x6c,  // ture2D (s_texFil
  0x74, 0x65, 0x72, 0x45, 0x78, 0x74, 0x72, 0x61, 0x32, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78,  // terExtra2, v_tex
  0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x2e, 0x78, 0x29, 0x20, 0x2b, 0x20, 0x28, 0x31, 0x2e,  // coord0).x) + (1.
  0x30, 0x20, 0x2d, 0x20, 0x75, 0x5f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x4d, 0x75, 0x6c,  // 0 - u_weightsMul
  0x2e, 0x7a, 0x29, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x7d, 0x3b, 0x0a, 0x20, 0x20,  // .z)));.    };.  
  0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x5f, 0x72, 0x67, 0x62, 0x5f, 0x34,  // };.  vec3 _rgb_4
  0x3b, 0x0a, 0x20, 0x20, 0x5f, 0x72, 0x67, 0x62, 0x5f, 0x34, 0x20, 0x3d, 0x20, 0x28, 0x74, 0x65,  // ;.  _rgb_4 = (te
  0x78, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x2a, 0x20, 0x28, 0x30, 0x2e, 0x33, 0x20, 0x2b,  // x_1.xyz * (0.3 +
  0x20, 0x28, 0x30, 0x2e, 0x37, 0x20, 0x2f, 0x20, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x63, 0x6c, 0x61,  //  (0.7 / .    cla
  0x6d, 0x70, 0x20, 0x28, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x2e, 0x78, 0x20,  // mp ((tmpvar_3.x 
  0x2b, 0x20, 0x30, 0x2e, 0x32, 0x29, 0x2c, 0x20, 0x30, 0x2e, 0x31, 0x2c, 0x20, 0x31, 0x2e, 0x30,  // + 0.2), 0.1, 1.0
  0x29, 0x0a, 0x20, 0x20, 0x29, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31,  // ).  )));.  tex_1
  0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x70, 0x6f, 0x77, 0x20, 0x28, 0x61, 0x62, 0x73, 0x28,  // .xyz = pow (abs(
  0x63, 0x6c, 0x61, 0x6d, 0x70, 0x20, 0x28, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x28, 0x28, 0x5f, 0x72,  // clamp (.    ((_r
  0x67, 0x62, 0x5f, 0x34, 0x20, 0x2a, 0x20, 0x28, 0x28, 0x32, 0x2e, 0x35, 0x31, 0x20, 0x2a, 0x20,  // gb_4 * ((2.51 * 
  0x5f, 0x72, 0x67, 0x62, 0x5f, 0x34, 0x29, 0x20, 0x2b, 0x20, 0x30, 0x2e, 0x30, 0x33, 0x29, 0x29,  // _rgb_4) + 0.03))
  0x20, 0x2f, 0x20, 0x28, 0x28, 0x5f, 0x72, 0x67, 0x62, 0x5f, 0x34, 0x20, 0x2a, 0x20, 0x28, 0x0a,  //  / ((_rgb_4 * (.
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x28, 0x32, 0x2e, 0x34, 0x33, 0x20, 0x2a, 0x20, 0x5f, 0x72,  //       (2.43 * _r
  0x67, 0x62, 0x5f, 0x34, 0x29, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2b, 0x20, 0x30, 0x2e, 0x35,  // gb_4).     + 0.5
  0x39, 0x29, 0x29, 0x20, 0x2b, 0x20, 0x30, 0x2e, 0x31, 0x34, 0x29, 0x29, 0x0a, 0x20, 0x20, 0x2c,  // 9)) + 0.14)).  ,
  0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29, 0x29, 0x2c, 0x20, 0x76, 0x65, 0x63,  //  0.0, 1.0)), vec
  0x33, 0x28, 0x30, 0x2e, 0x34, 0x35, 0x34, 0x35, 0x34, 0x35, 0x34, 0x2c, 0x20, 0x30, 0x2e, 0x34,  // 3(0.4545454, 0.4
  0x35, 0x34, 0x35, 0x34, 0x35, 0x34, 0x2c, 0x20, 0x30, 0x2e, 0x34, 0x35, 0x34, 0x35, 0x34, 0x35,  // 545454, 0.454545
  0x34, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f,  // 4));.  gl_FragCo
  0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x74, 0x65, 0x78, 0x5f, 0x31, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a,  // lor = tex_1;.}..
  0x00 };                                                                                          // or = tex_1;.}...
unsigned int fs_tonemapping_ch3_bin_glsl_size = 1841;

BX_UNUSED(fs_tonemapping_ch3_bin_glsl)
BX_UNUSED(fs_tonemapping_ch3_bin_glsl_size)
static const uint8_t * fs_tonemapping_ch3_bin_dx9 = NULL;
unsigned int fs_tonemapping_ch3_bin_dx9_size = 0;

BX_UNUSED(fs_tonemapping_ch3_bin_dx9)
BX_UNUSED(fs_tonemapping_ch3_bin_dx9_size)
static const uint8_t * fs_tonemapping_ch3_bin_dx11 = NULL;
unsigned int fs_tonemapping_ch3_bin_dx11_size = 0;

BX_UNUSED(fs_tonemapping_ch3_bin_dx11)
BX_UNUSED(fs_tonemapping_ch3_bin_dx11_size)
static const uint8_t * fs_tonemapping_ch3_bin_metal = NULL;
unsigned int fs_tonemapping_ch3_bin_metal_size = 0;

BX_UNUSED(fs_tonemapping_ch3_bin_metal)
BX_UNUSED(fs_tonemapping_ch3_bin_metal_size)
static const uint8_t * fs_tonemapping_ch3_bin_spirv = NULL;
unsigned int fs_tonemapping_ch3_bin_spirv_size = 0;

BX_UNUSED(fs_tonemapping_ch3_bin_spirv)
BX_UNUSED(fs_tonemapping_ch3_bin_spirv_size)
static const uint8_t * fs_tonemapping_ch3_bin_esslandroid = NULL;
unsigned int fs_tonemapping_ch3_bin_esslandroid_size = 0;

BX_UNUSED(fs_tonemapping_ch3_bin_esslandroid)
BX_UNUSED(fs_tonemapping_ch3_bin_esslandroid_size)
static const uint8_t * fs_tonemapping_ch3_bin_pssl = NULL;
unsigned int fs_tonemapping_ch3_bin_pssl_size = 0;

BX_UNUSED(fs_tonemapping_ch3_bin_pssl)
BX_UNUSED(fs_tonemapping_ch3_bin_pssl_size)
static const uint8_t * fs_tonemapping_ch3_bin_esslnacl = NULL;
unsigned int fs_tonemapping_ch3_bin_esslnacl_size = 0;

BX_UNUSED(fs_tonemapping_ch3_bin_esslnacl)
BX_UNUSED(fs_tonemapping_ch3_bin_esslnacl_size)
