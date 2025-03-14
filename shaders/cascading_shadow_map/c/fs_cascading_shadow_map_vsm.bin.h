static const uint8_t fs_cascading_shadow_map_vsm_bin_glsl[] = {
  0x46, 0x53, 0x48, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaf, 0x00,  // FSH.............
  0x00, 0x00, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b,  // ..void main ().{
  0x0a, 0x20, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31,  // .  vec4 tmpvar_1
  0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x7a, 0x77, 0x20,  // ;.  tmpvar_1.zw 
  0x3d, 0x20, 0x76, 0x65, 0x63, 0x32, 0x28, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29,  // = vec2(0.0, 1.0)
  0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x78, 0x20, 0x3d,  // ;.  tmpvar_1.x =
  0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6f, 0x72, 0x64, 0x2e, 0x7a, 0x3b,  //  gl_FragCoord.z;
  0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, 0x79, 0x20, 0x3d, 0x20,  // .  tmpvar_1.y = 
  0x28, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6f, 0x72, 0x64, 0x2e, 0x7a, 0x20,  // (gl_FragCoord.z 
  0x2a, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6f, 0x72, 0x64, 0x2e, 0x7a,  // * gl_FragCoord.z
  0x29, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f,  // );.  gl_FragColo
  0x72, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x7d, 0x0a,  // r = tmpvar_1;.}.
  0x0a, 0x00 };                                                                                    // = tmpvar_1;.}...
unsigned int fs_cascading_shadow_map_vsm_bin_glsl_size = 194;

BX_UNUSED(fs_cascading_shadow_map_vsm_bin_glsl)
BX_UNUSED(fs_cascading_shadow_map_vsm_bin_glsl_size)
static const uint8_t fs_cascading_shadow_map_vsm_bin_dx9[] = {
  0x46, 0x53, 0x48, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x01,  // FSH.............
  0x00, 0x00, 0x44, 0x58, 0x42, 0x43, 0x82, 0xfa, 0x07, 0x52, 0x31, 0x7a, 0x20, 0x25, 0xd9, 0x82,  // ..DXBC...R1z %..
  0xf4, 0xbf, 0xdb, 0x74, 0xec, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x14, 0x01, 0x00, 0x00, 0x03, 0x00,  // ...t............
  0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x49, 0x53,  // ..,...`.......IS
  0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00,  // GN,........... .
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,  // ................
  0x00, 0x00, 0x0f, 0x04, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f,  // ......SV_POSITIO
  0x4e, 0x00, 0x4f, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00,  // N.OSGN,.........
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,  // .. .............
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, 0x52,  // ..........SV_TAR
  0x47, 0x45, 0x54, 0x00, 0xab, 0xab, 0x53, 0x48, 0x44, 0x52, 0x78, 0x00, 0x00, 0x00, 0x40, 0x00,  // GET...SHDRx...@.
  0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x64, 0x20, 0x00, 0x04, 0x42, 0x10, 0x10, 0x00, 0x00, 0x00,  // ......d ..B.....
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00,  // ......e.... ....
  0x00, 0x00, 0x38, 0x00, 0x00, 0x07, 0x22, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x10,  // ..8..." ......*.
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00,  // ......*.......6.
  0x00, 0x05, 0x12, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x10, 0x10, 0x00, 0x00, 0x00,  // ... ......*.....
  0x00, 0x00, 0x36, 0x00, 0x00, 0x08, 0xc2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40,  // ..6.... .......@
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // ................
  0x80, 0x3f, 0x3e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 };                                    // .......?>.......
unsigned int fs_cascading_shadow_map_vsm_bin_dx9_size = 298;

BX_UNUSED(fs_cascading_shadow_map_vsm_bin_dx9)
BX_UNUSED(fs_cascading_shadow_map_vsm_bin_dx9_size)
static const uint8_t fs_cascading_shadow_map_vsm_bin_dx11[] = {
  0x46, 0x53, 0x48, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01,  // FSH.............
  0x00, 0x00, 0x44, 0x58, 0x42, 0x43, 0xa0, 0xdb, 0xb0, 0xd6, 0x3d, 0xaa, 0x98, 0xcb, 0xf5, 0x26,  // ..DXBC....=....&
  0xc6, 0xf8, 0xdf, 0x85, 0x05, 0x89, 0x01, 0x00, 0x00, 0x00, 0x18, 0x01, 0x00, 0x00, 0x03, 0x00,  // ................
  0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x49, 0x53,  // ..,...`.......IS
  0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00,  // GN,........... .
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,  // ................
  0x00, 0x00, 0x0f, 0x04, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f,  // ......SV_POSITIO
  0x4e, 0x00, 0x4f, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00,  // N.OSGN,.........
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,  // .. .............
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, 0x52,  // ..........SV_TAR
  0x47, 0x45, 0x54, 0x00, 0xab, 0xab, 0x53, 0x48, 0x45, 0x58, 0x7c, 0x00, 0x00, 0x00, 0x50, 0x00,  // GET...SHEX|...P.
  0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x6a, 0x08, 0x00, 0x01, 0x64, 0x20, 0x00, 0x04, 0x42, 0x10,  // ......j...d ..B.
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20,  // ..........e.... 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x07, 0x22, 0x20, 0x10, 0x00, 0x00, 0x00,  // ......8..." ....
  0x00, 0x00, 0x2a, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x10, 0x10, 0x00, 0x00, 0x00,  // ..*.......*.....
  0x00, 0x00, 0x36, 0x00, 0x00, 0x05, 0x12, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x10,  // ..6.... ......*.
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x08, 0xc2, 0x20, 0x10, 0x00, 0x00, 0x00,  // ......6.... ....
  0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // ...@............
  0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x3e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 };            // .......?>.......
unsigned int fs_cascading_shadow_map_vsm_bin_dx11_size = 302;

BX_UNUSED(fs_cascading_shadow_map_vsm_bin_dx11)
BX_UNUSED(fs_cascading_shadow_map_vsm_bin_dx11_size)
static const uint8_t fs_cascading_shadow_map_vsm_bin_metal[] = {
  0x46, 0x53, 0x48, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x01,  // FSH...........c.
  0x00, 0x00, 0x23, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, 0x20, 0x3c, 0x6d, 0x65, 0x74, 0x61,  // ..#include <meta
  0x6c, 0x5f, 0x73, 0x74, 0x64, 0x6c, 0x69, 0x62, 0x3e, 0x0a, 0x23, 0x69, 0x6e, 0x63, 0x6c, 0x75,  // l_stdlib>.#inclu
  0x64, 0x65, 0x20, 0x3c, 0x73, 0x69, 0x6d, 0x64, 0x2f, 0x73, 0x69, 0x6d, 0x64, 0x2e, 0x68, 0x3e,  // de <simd/simd.h>
  0x0a, 0x0a, 0x75, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63,  // ..using namespac
  0x65, 0x20, 0x6d, 0x65, 0x74, 0x61, 0x6c, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74,  // e metal;..struct
  0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74,  //  xlatMtlMain_out
  0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x62, 0x67,  // .{.    float4 bg
  0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, 0x5b, 0x5b, 0x63,  // fx_FragData0 [[c
  0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x66,  // olor(0)]];.};..f
  0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d,  // ragment xlatMtlM
  0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d,  // ain_out xlatMtlM
  0x61, 0x69, 0x6e, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72,  // ain(float4 gl_Fr
  0x61, 0x67, 0x43, 0x6f, 0x6f, 0x72, 0x64, 0x20, 0x5b, 0x5b, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69,  // agCoord [[positi
  0x6f, 0x6e, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x78, 0x6c, 0x61, 0x74,  // on]]).{.    xlat
  0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x6f, 0x75, 0x74, 0x20,  // MtlMain_out out 
  0x3d, 0x20, 0x7b, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, 0x2e, 0x62, 0x67,  // = {};.    out.bg
  0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, 0x3d, 0x20, 0x66,  // fx_FragData0 = f
  0x6c, 0x6f, 0x61, 0x74, 0x34, 0x28, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6f,  // loat4(gl_FragCoo
  0x72, 0x64, 0x2e, 0x7a, 0x2c, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6f,  // rd.z, gl_FragCoo
  0x72, 0x64, 0x2e, 0x7a, 0x20, 0x2a, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f,  // rd.z * gl_FragCo
  0x6f, 0x72, 0x64, 0x2e, 0x7a, 0x2c, 0x20, 0x30, 0x2e, 0x30, 0x2c, 0x20, 0x31, 0x2e, 0x30, 0x29,  // ord.z, 0.0, 1.0)
  0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x6f, 0x75, 0x74,  // ;.    return out
  0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0x00 };                                          // urn out;.}......
unsigned int fs_cascading_shadow_map_vsm_bin_metal_size = 377;

BX_UNUSED(fs_cascading_shadow_map_vsm_bin_metal)
BX_UNUSED(fs_cascading_shadow_map_vsm_bin_metal_size)
static const uint8_t fs_cascading_shadow_map_vsm_bin_spirv[] = {
  0x46, 0x53, 0x48, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x02,  // FSH.............
  0x00, 0x00, 0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x00, 0x08, 0x00, 0x57, 0x00,  // ....#.........W.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00,  // ................
  0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34,  // ......GLSL.std.4
  0x35, 0x30, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,  // 50..............
  0x00, 0x00, 0x0f, 0x00, 0x07, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61,  // ..............ma
  0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x10, 0x00,  // in....+...4.....
  0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x05, 0x00,  // ................
  0x00, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61,  // ..............ma
  0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x67, 0x6c,  // in........+...gl
  0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6f, 0x72, 0x64, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00,  // _FragCoord......
  0x06, 0x00, 0x34, 0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44,  // ..4...bgfx_FragD
  0x61, 0x74, 0x61, 0x30, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x0b, 0x00,  // ata0..G...+.....
  0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x34, 0x00, 0x00, 0x00, 0x1e, 0x00,  // ......G...4.....
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x00,  // ..............!.
  0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x06, 0x00,  // ................
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x06, 0x00,  // .. .............
  0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1b, 0x00,  // ......+.........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x27, 0x00,  // ......+.......'.
  0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x20, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x01, 0x00,  // .....? ...*.....
  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x2b, 0x00,  // ......;...*...+.
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x33, 0x00, 0x00, 0x00, 0x03, 0x00,  // ...... ...3.....
  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x33, 0x00, 0x00, 0x00, 0x34, 0x00,  // ......;...3...4.
  0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00,  // ......6.........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, 0x00,  // ................
  0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x2b, 0x00,  // ..=.......,...+.
  0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x2c, 0x00,  // ..Q.......P...,.
  0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x52, 0x00,  // ......Q.......R.
  0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x06, 0x00,  // ..,.......Q.....
  0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x85, 0x00,  // ..T...,.........
  0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00, 0x54, 0x00,  // ......U...R...T.
  0x00, 0x00, 0x50, 0x00, 0x07, 0x00, 0x08, 0x00, 0x00, 0x00, 0x56, 0x00, 0x00, 0x00, 0x50, 0x00,  // ..P.......V...P.
  0x00, 0x00, 0x55, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x3e, 0x00,  // ..U.......'...>.
  0x03, 0x00, 0x34, 0x00, 0x00, 0x00, 0x56, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00,  // ..4...V.......8.
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };                                                            // V.......8.......
unsigned int fs_cascading_shadow_map_vsm_bin_spirv_size = 550;

BX_UNUSED(fs_cascading_shadow_map_vsm_bin_spirv)
BX_UNUSED(fs_cascading_shadow_map_vsm_bin_spirv_size)
static const uint8_t * fs_cascading_shadow_map_vsm_bin_esslandroid = NULL;
unsigned int fs_cascading_shadow_map_vsm_bin_esslandroid_size = 0;

BX_UNUSED(fs_cascading_shadow_map_vsm_bin_esslandroid)
BX_UNUSED(fs_cascading_shadow_map_vsm_bin_esslandroid_size)
static const uint8_t * fs_cascading_shadow_map_vsm_bin_pssl = NULL;
unsigned int fs_cascading_shadow_map_vsm_bin_pssl_size = 0;

BX_UNUSED(fs_cascading_shadow_map_vsm_bin_pssl)
BX_UNUSED(fs_cascading_shadow_map_vsm_bin_pssl_size)
static const uint8_t * fs_cascading_shadow_map_vsm_bin_esslnacl = NULL;
unsigned int fs_cascading_shadow_map_vsm_bin_esslnacl_size = 0;

BX_UNUSED(fs_cascading_shadow_map_vsm_bin_esslnacl)
BX_UNUSED(fs_cascading_shadow_map_vsm_bin_esslnacl_size)
