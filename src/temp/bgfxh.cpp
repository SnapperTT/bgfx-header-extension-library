// bgfxh.cpp
//

#include "bgfxh.hh"
#include <fstream> // Todo - make fstream dependency optional

#ifdef BGFXH_EMBED_DEBUG_SHADERS
	#include "bgfxh_embedded_shader.h"
#endif //BGFXH_EMBED_DEBUG_SHADERS

#define LZZ_INLINE inline
namespace bgfxh
{
  static unsigned int const SAMPLER_COLOR = 0;
}
namespace bgfxh
{
  static unsigned int const SAMPLER_LUM = 1;
}
namespace bgfxh
{
  static unsigned int const SAMPLER_TONEMAPING_EXTRA0 = 2;
}
namespace bgfxh
{
  static unsigned int const SAMPLER_TONEMAPING_EXTRA1 = 3;
}
namespace bgfxh
{
  static unsigned int const SAMPLER_TONEMAPING_EXTRA2 = 4;
}
namespace bgfxh
{
  static unsigned int const SAMPLER_TONEMAPING_EXTRA3 = 5;
}
namespace bgfxh
{
  static bx::Vec3 intersectPlanes (bx::Plane const & p1, bx::Plane const & p2, bx::Plane const & p3);
}
namespace bgfxh
{
  unsigned int screenWidth = 0;
}
namespace bgfxh
{
  unsigned int screenHeight = 0;
}
namespace bgfxh
{
  BGFXH_STRING shaderSearchPath = "";
}
namespace bgfxh
{
  bgfx::UniformHandle s_texColor = BGFX_INVALID_HANDLE;
}
namespace bgfxh
{
  bgfx::ProgramHandle m_programUntexturedPassthrough = BGFX_INVALID_HANDLE;
}
namespace bgfxh
{
  bgfx::ProgramHandle m_programUntexturedPassthroughColor = BGFX_INVALID_HANDLE;
}
namespace bgfxh
{
  bgfx::ProgramHandle m_programTexturePassthrough = BGFX_INVALID_HANDLE;
}
namespace bgfxh
{
  bgfx::ProgramHandle m_programTexturePassthroughArray = BGFX_INVALID_HANDLE;
}
namespace bgfxh
{
  bgfx::ProgramHandle m_programTexturePassthroughMonochromatic = BGFX_INVALID_HANDLE;
}
namespace bgfxh
{
  bgfx::UniformHandle u_bgfxhUtilUniform = BGFX_INVALID_HANDLE;
}
namespace bgfxh
{
  bx::AllocatorI * m_allocator = NULL;
}
namespace bgfxh
{
  BGFXH_STRING getShaderDirectoryFromRenderType ()
                                                         {
		bgfx::RendererType::Enum type = bgfx::getRendererType();
			
		switch (type) {
			case bgfx::RendererType::Noop:
			//case bgfx::RendererType::Direct3D9:  return "dx9";   break;
			case bgfx::RendererType::Direct3D11:
			case bgfx::RendererType::Direct3D12: return "dx11";  break;
			case bgfx::RendererType::Gnm:        return "pssl";  break;
			case bgfx::RendererType::Metal:      return "metal"; break;
			case bgfx::RendererType::Nvn:        return "nvn";   break;
			case bgfx::RendererType::OpenGL:     return "glsl";  break;
			#ifdef BGFXH_GOOGLE_NACL
				case bgfx::RendererType::OpenGLES:   return "esslnacl";  break;
			#else
				case bgfx::RendererType::OpenGLES:   return "essl";  break;
			#endif
			case bgfx::RendererType::Vulkan:     return "spirv"; break;
			default: break;
			}
		BGFXH_ASSERT (false, "bgfxh::getShaderDirectoryFromRenderType() - Invalid render type!");
		return "i am error";
		}
}
namespace bgfxh
{
  void init (unsigned int const _screenWidth, unsigned int const _screenHeight, BGFXH_STRING const & _shaderSearchPath)
                                                                                                                              {
		screenWidth  = _screenWidth;
		screenHeight = _screenHeight;
		shaderSearchPath = _shaderSearchPath;
		PosVertex::init();
		PosTexCoord0Vertex::init();
		if (!m_allocator)
			m_allocator = bgfxh::internal_getDefaultAllocator();
		
		s_texColor  = bgfx::createUniform("s_texColor",  bgfx::UniformType::Sampler);
		u_bgfxhUtilUniform = bgfx::createUniform("u_bgfxhUtilUniform",  bgfx::UniformType::Vec4);
		
		#ifdef BGFXH_EMBED_DEBUG_SHADERS
			{
			#include "shaders/textured_passthrough/c/vs_textured_passthrough.bin.h"
			#include "shaders/textured_passthrough/c/fs_textured_passthrough.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_textured_passthrough_bin),
				BGFXH_EMBEDDED_SHADER(fs_textured_passthrough_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programTexturePassthrough = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_textured_passthrough_bin")
															, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_textured_passthrough_bin")
															, true
															);
			}
			{
			#include "shaders/textured_passthrough/c/vs_textured_passthrough_monochromatic.bin.h"
			#include "shaders/textured_passthrough/c/fs_textured_passthrough_monochromatic.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_textured_passthrough_monochromatic_bin),
				BGFXH_EMBEDDED_SHADER(fs_textured_passthrough_monochromatic_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programTexturePassthroughMonochromatic = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_textured_passthrough_monochromatic_bin")
															, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_textured_passthrough_monochromatic_bin")
															, true
															);
			}
			
			{
			#include "shaders/textured_passthrough/c/vs_untextured_passthrough.bin.h"
			#include "shaders/textured_passthrough/c/fs_untextured_passthrough.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_untextured_passthrough_bin),
				BGFXH_EMBEDDED_SHADER(fs_untextured_passthrough_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programUntexturedPassthrough = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_untextured_passthrough_bin")
															, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_untextured_passthrough_bin")
															, true
															);
			}
			
			{
			#include "shaders/textured_passthrough/c/vs_untextured_passthrough_color.bin.h"
			#include "shaders/textured_passthrough/c/fs_untextured_passthrough_color.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_untextured_passthrough_color_bin),
				BGFXH_EMBEDDED_SHADER(fs_untextured_passthrough_color_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programUntexturedPassthroughColor = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_untextured_passthrough_color_bin")
															, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_untextured_passthrough_color_bin")
															, true
															);
			}
			
			{
			#include "shaders/textured_passthrough/c/vs_textured_passthrough_array.bin.h"
			#include "shaders/textured_passthrough/c/fs_textured_passthrough_array.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_textured_passthrough_array_bin),
				BGFXH_EMBEDDED_SHADER(fs_textured_passthrough_array_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programTexturePassthroughArray = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_textured_passthrough_array_bin")
															, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_textured_passthrough_array_bin")
															, true
															);
			}
		#else
			m_programTexturePassthrough = bgfxh::loadProgram (bgfxh::shaderSearchPath + "vs_textured_passthrough", bgfxh::shaderSearchPath + "fs_textured_passthrough");
			m_programTexturePassthroughMonochromatic = bgfxh::loadProgram (bgfxh::shaderSearchPath + "vs_textured_passthrough_monochromatic", bgfxh::shaderSearchPath + "fs_textured_passthrough_monochromatic");
			m_programUntexturedPassthrough = bgfxh::loadProgram (bgfxh::shaderSearchPath + "vs_untextured_passthrough", bgfxh::shaderSearchPath + "fs_untextured_passthrough");
			m_programUntexturedPassthroughColor = bgfxh::loadProgram (bgfxh::shaderSearchPath + "vs_untextured_passthrough_color", bgfxh::shaderSearchPath + "fs_untextured_passthrough_color");
			m_programTexturePassthroughArray = bgfxh::loadProgram (bgfxh::shaderSearchPath + "vs_textured_passthrough_array", bgfxh::shaderSearchPath + "fs_textured_passthrough_array");
		#endif // BGFXH_EMBED_DEBUG_SHADERS
		
		BGFXH_ASSERT(bgfx::isValid(m_programTexturePassthrough), "m_programTexturePassthrough");
		BGFXH_ASSERT(bgfx::isValid(m_programTexturePassthroughMonochromatic), "m_programTexturePassthroughMonochromatic");
		BGFXH_ASSERT(bgfx::isValid(m_programUntexturedPassthrough), "m_programUntexturedPassthrough");
		BGFXH_ASSERT(bgfx::isValid(m_programUntexturedPassthroughColor), "m_programUntexturedPassthroughColor");
		BGFXH_ASSERT(bgfx::isValid(m_programTexturePassthroughArray), "m_programTexturePassthroughArray");
		}
}
namespace bgfxh
{
  bx::AllocatorI * internal_getDefaultAllocator ()
                                                       {
		static bx::DefaultAllocator s_allocator;
		return &s_allocator;
		}
}
namespace bgfxh
{
  void debugDrawTexture (bgfx::ViewId const viewId, bgfx::TextureHandle const texture, float const xOffset, float const yOffset, float const xSize, float const ySize, float const _targetFrameBufferWidth, float const _targetFrameBufferHeight)
                                                                                                                                                                                                                                                                      {
		debugDrawTextureUv(viewId, texture, xOffset, yOffset, xSize, ySize, 0.f, 1.f, 0.f, 1.f);
		}
}
namespace bgfxh
{
  void debugDrawTextureUv (bgfx::ViewId const viewId, bgfx::TextureHandle const texture, float const xOffset, float const yOffset, float const xSize, float const ySize, float const _minu, float const _maxu, float const _minv, float const _maxv)
                                                                                                                                                                                                                                                           {
		if (!bgfx::isValid(texture)) return;
		bgfx::setTexture (SAMPLER_COLOR, s_texColor, texture);
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		screenSpaceQuadUv (xOffset, yOffset, xSize, ySize, _minu, _maxu, _minv, _maxv);
		bgfx::submit (viewId, m_programTexturePassthrough);
		}
}
namespace bgfxh
{
  void debugDrawTextureArray (bgfx::ViewId const viewId, bgfx::TextureHandle const texture, unsigned int const layer, float const xOffset, float const yOffset, float const xSize, float const ySize, float const _targetFrameBufferWidth, float const _targetFrameBufferHeight)
                                                                                                                                                                                                                                                                                                     {
		debugDrawTextureArrayUv(viewId, texture, layer, xOffset, yOffset, xSize, ySize, 0.f, 1.f, 0.f, 1.f);
		}
}
namespace bgfxh
{
  void debugDrawTextureArrayUv (bgfx::ViewId const viewId, bgfx::TextureHandle const texture, unsigned int const layer, float const xOffset, float const yOffset, float const xSize, float const ySize, float const _minu, float const _maxu, float const _minv, float const _maxv)
                                                                                                                                                                                                                                                                                          {
		if (!bgfx::isValid(texture)) return;
		bgfx::setTexture (SAMPLER_COLOR, s_texColor, texture);
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		float v[4] = { float(layer), 0.f, 0.f, 0.f };
		bgfx::setUniform(u_bgfxhUtilUniform, v);
		screenSpaceQuadUv (xOffset, yOffset, xSize, ySize, _minu, _maxu, _minv, _maxv);
		bgfx::submit (viewId, m_programTexturePassthroughArray);
		}
}
namespace bgfxh
{
  void debugDrawFramebuffer (bgfx::ViewId const viewId, bgfx::FrameBufferHandle const framebuffer, float const xOffset, float const yOffset, float const xSize, float const ySize, float const _targetFrameBufferWidth, float const _targetFrameBufferHeight)
                                                                                                                                                                                                                                                                                  {
		debugDrawTextureUv (viewId, bgfx::getTexture(framebuffer, 0), xOffset, yOffset, xSize, ySize, 0.f, 1.f, 0.f, 1.f);
		}
}
namespace bgfxh
{
  void debugDrawFramebufferUv (bgfx::ViewId const viewId, bgfx::FrameBufferHandle const framebuffer, float const xOffset, float const yOffset, float const xSize, float const ySize, float const _minu, float const _maxu, float const _minv, float const _maxv)
                                                                                                                                                                                                                                                                       {
		debugDrawTextureUv (viewId, bgfx::getTexture(framebuffer, 0), xOffset, yOffset, xSize, ySize, _minu, _maxu, _minv, _maxv);
		}
}
namespace bgfxh
{
  void debugDrawTextureMono (bgfx::ViewId const viewId, bgfx::TextureHandle const texture, float const xOffset, float const yOffset, float const xSize, float const ySize, float const _targetFrameBufferWidth, float const _targetFrameBufferHeight)
                                                                                                                                                                                                                                                                          {
		debugDrawTextureMonoUv(viewId, texture, xOffset, yOffset, xSize, ySize, 0.f, 1.f, 0.f, 1.f);
		}
}
namespace bgfxh
{
  void debugDrawTextureMonoUv (bgfx::ViewId const viewId, bgfx::TextureHandle const texture, float const xOffset, float const yOffset, float const xSize, float const ySize, float const _minu, float const _maxu, float const _minv, float const _maxv)
                                                                                                                                                                                                                                                               {
		if (!bgfx::isValid(texture)) return;
		bgfx::setTexture (SAMPLER_COLOR, s_texColor, texture);
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		screenSpaceQuadUv (xOffset, yOffset, xSize, ySize, _minu, _maxu, _minv, _maxv);
		bgfx::submit (viewId, m_programTexturePassthroughMonochromatic);
		}
}
namespace bgfxh
{
  void debugDrawFramebufferMono (bgfx::ViewId const viewId, bgfx::FrameBufferHandle const framebuffer, float const xOffset, float const yOffset, float const xSize, float const ySize, float const _targetFrameBufferWidth, float const _targetFrameBufferHeight)
                                                                                                                                                                                                                                                                                      {
		debugDrawTextureMono (viewId, bgfx::getTexture(framebuffer, 0), xOffset, yOffset, xSize, ySize, _targetFrameBufferWidth, _targetFrameBufferHeight);
		}
}
namespace bgfxh
{
  void deInit ()
                       {
		destroyHandle (m_programUntexturedPassthroughColor);
		destroyHandle (m_programUntexturedPassthrough);
		destroyHandle (m_programTexturePassthrough);
		destroyHandle (m_programTexturePassthroughArray);
		destroyHandle (m_programTexturePassthroughMonochromatic);
		destroyHandle (s_texColor);
		destroyHandle (u_bgfxhUtilUniform);
		}
}
namespace bgfxh
{
  bgfx::TextureHandle renderJob::getOutputTexture () const
                                                                      { /// Returns the output framebuffer as a texture handle. Use this to use the output of a filter as a sampler input to another
			bgfx::FrameBufferHandle ofb = getOutputFrameBuffer();
			if (!bgfx::isValid(ofb)) return BGFX_INVALID_HANDLE;
			return bgfx::getTexture(getOutputFrameBuffer(), 0);
			}
}
namespace bgfxh
{
  void frustum::setFromViewAndProjMatrix (float * mView, float * mProj)
                                                                             {
			float res[4][4];
			bx::mtxMul((float *) res, mView, mProj);
			
			bx::Plane & left =  planes[0];
			bx::Plane & right = planes[1];
			bx::Plane & top =   planes[2];
			bx::Plane & bottom = planes[3];
			left.normal   = bx::Vec3(res[0][3] + res[0][0], res[1][3] + res[1][0], res[2][3] + res[2][0]); left.dist   = (res[3][3] + res[3][0]);
			right.normal  = bx::Vec3(res[0][3] - res[0][0], res[1][3] - res[1][0], res[2][3] - res[2][0]); right.dist  = (res[3][3] - res[3][0]);
			top.normal    = bx::Vec3(res[0][3] - res[0][1], res[1][3] - res[1][1], res[2][3] - res[2][1]); top.dist    = (res[3][3] - res[3][1]);
			bottom.normal = bx::Vec3(res[0][3] + res[0][1], res[1][3] + res[1][1], res[2][3] + res[2][1]); bottom.dist = (res[3][3] + res[3][1]);
			
			// Normalize the planes
			for (unsigned int i = 0; i < 4; ++i) {
				float invLen = 1.0/length(planes[i].v.normal);
				planes[i].v.normal = bx::mul(planes[i].v.normal, invLen);
				planes[i].v.dist   *= invLen;
				}
			}
}
namespace bgfxh
{
  void PosTexCoord0Vertex::init ()
                                   {
			ms_decl.begin()
				.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
			}
}
namespace bgfxh
{
  bgfx::VertexLayout PosTexCoord0Vertex::ms_decl;
}
namespace bgfxh
{
  void PosVertex::init ()
                                   {
			ms_decl.begin()
				.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.end();
			}
}
namespace bgfxh
{
  bgfx::VertexLayout PosVertex::ms_decl;
}
namespace bgfxh
{
  void initView (bgfx::ViewId const viewId, char const * tag, uint32_t const vw, uint32_t const vh, float const (view) [16], float const (proj) [16], bgfx::FrameBufferHandle const fh, bool const doClear, bool const forwardZ)
                                                                                                                                                                                                                                               {
		bgfx::setViewName(viewId, tag);
		bgfx::setViewRect(viewId, 0, 0, vw, vh);
		bgfx::setViewTransform(viewId, view, proj);
		bgfx::setViewFrameBuffer(viewId, fh);
		
		const uint16_t clearFlags = doClear ? (BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH) : 0;
		const float clearDepth = (forwardZ ? 1.0f : 0.0f);
		const uint8_t clearStencil = 0;
		const uint32_t clearColour = 0x00000000;
		bgfx::setViewClear(viewId, clearFlags, clearColour, clearDepth, clearStencil);
		}
}
namespace bgfxh
{
  void initView2D (bgfx::ViewId const viewId, char const * tag, uint32_t const vw, uint32_t const vh, bgfx::FrameBufferHandle const fh, bool const doClear, bool const unitOrthoMatrix, bool const forwardZ)
                                                                                                                                                                                                                                        {
		float orthoProj[16];	// Ortho matrix for rendering screenspace quads
		if (unitOrthoMatrix)
			bx::mtxOrtho(orthoProj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f, 0.0f, bgfx::getCaps()->homogeneousDepth); // flip bottom 0.0f and viewHeight if you don't like bottom left coordinates
		else
			bx::mtxOrtho(orthoProj, 0.0f, vw, vh, 0.0f, 0.0f, 100.0f, 0.0f, bgfx::getCaps()->homogeneousDepth);
		
		bgfx::setViewName(viewId, tag);
		bgfx::setViewRect(viewId, 0, 0, vw, vh);
		bgfx::setViewTransform(viewId, NULL, orthoProj);
		bgfx::setViewFrameBuffer(viewId, fh);
		
		const uint16_t clearFlags = doClear ? (BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH) : 0;
		const float clearDepth = (forwardZ ? 1.0f : 0.0f);
		const uint8_t clearStencil = 0;
		const uint32_t clearColour = 0x00000000;
		bgfx::setViewClear(viewId, clearFlags, clearColour, clearDepth, clearStencil);
		}
}
namespace bgfxh
{
  void fullscreenQuad (float const _textureWidth, float const _textureHeight)
                                                                                   {
		/*
		* From the BGFX Examples, the following license applies to only this function:
		* Copyright 2011-2018 Branimir Karadzic. All rights reserved.
		* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
		*/
		//const bgfx::RendererType::Enum renderer = bgfx::getRendererType();
		const float _texelHalf = 0.0f;//bgfx::RendererType::Direct3D9 == renderer ? 0.5f : 0.0f;
		const bool _originBottomLeft = bgfx::getCaps()->originBottomLeft;
		const float _width = 1.0f;
		const float _height = 1.0f;
		
		if (3 == bgfx::getAvailTransientVertexBuffer(3, bgfxh::PosTexCoord0Vertex::ms_decl) ) {
			bgfx::TransientVertexBuffer vb;
			bgfx::allocTransientVertexBuffer(&vb, 3, bgfxh::PosTexCoord0Vertex::ms_decl);
			bgfxh::PosTexCoord0Vertex* vertex = (bgfxh::PosTexCoord0Vertex*)vb.data;

			const float minx = -_width;
			const float maxx =  _width;
			const float miny = 0.0f;
			const float maxy = _height*2.0f;

			const float texelHalfW = _texelHalf/_textureWidth;
			const float texelHalfH = _texelHalf/_textureHeight;
			const float minu = -1.0f + texelHalfW;
			const float maxu =  1.0f + texelHalfH;

			const float zz = 0.0f;

			float minv = texelHalfH;
			float maxv = 2.0f + texelHalfH;

			if (_originBottomLeft) {
				float temp = minv;
				minv = maxv;
				maxv = temp;

				minv -= 1.0f;
				maxv -= 1.0f;
				}

			vertex[0].m_x = minx;
			vertex[0].m_y = miny;
			vertex[0].m_z = zz;
			vertex[0].m_u = minu;
			vertex[0].m_v = minv;

			vertex[1].m_x = maxx;
			vertex[1].m_y = miny;
			vertex[1].m_z = zz;
			vertex[1].m_u = maxu;
			vertex[1].m_v = minv;

			vertex[2].m_x = maxx;
			vertex[2].m_y = maxy;
			vertex[2].m_z = zz;
			vertex[2].m_u = maxu;
			vertex[2].m_v = maxv;

			bgfx::setVertexBuffer(0, &vb);
			}
		}
}
namespace bgfxh
{
  void screenSpaceQuad (float const xOffset, float const yOffset, float const xSize, float const ySize, float const _unused__framebufferWidth, float const _unused_framebufferHeight)
                                                                                                                                                                                                       {
		screenSpaceQuadUv(xOffset, yOffset, xSize, ySize, 0.0f, 1.0f, 0.0f, 1.0f);
		}
}
namespace bgfxh
{
  void screenSpaceQuadUv (float const xOffset, float const yOffset, float const xSize, float const ySize, float const _minu, float const _maxu, float const _minv, float const _maxv)
                                                                                                                                                                                           {
		/*
		* From the BGFX Examples, the following license applies to only this function:
		* Copyright 2011-2018 Branimir Karadzic. All rights reserved.
		* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
		*/
		const bool _originBottomLeft = bgfx::getCaps()->originBottomLeft;
		
		if (6 == bgfx::getAvailTransientVertexBuffer(6, bgfxh::PosTexCoord0Vertex::ms_decl) ) {
			bgfx::TransientVertexBuffer vb;
			bgfx::allocTransientVertexBuffer(&vb, 6, bgfxh::PosTexCoord0Vertex::ms_decl);
			bgfxh::PosTexCoord0Vertex* vertex = (bgfxh::PosTexCoord0Vertex*)vb.data;

			const float minx = xOffset;
			const float maxx = (xOffset + xSize);
			const float miny = yOffset;
			const float maxy = (yOffset + ySize);

			const float minu = _minu;
			const float maxu = _maxu;

			const float zz = 0.0f;

			float minv = _minv;
			float maxv = _maxv;

			if (_originBottomLeft) {
				float temp = minv;
				minv = maxv;
				maxv = temp;
				}

			vertex[0].m_x = minx;
			vertex[0].m_y = miny;
			vertex[0].m_z = zz;
			vertex[0].m_u = minu;
			vertex[0].m_v = minv;

			vertex[1].m_x = maxx;
			vertex[1].m_y = miny;
			vertex[1].m_z = zz;
			vertex[1].m_u = maxu;
			vertex[1].m_v = minv;

			vertex[2].m_x = maxx;
			vertex[2].m_y = maxy;
			vertex[2].m_z = zz;
			vertex[2].m_u = maxu;
			vertex[2].m_v = maxv;
			
			vertex[3].m_x = minx;
			vertex[3].m_y = miny;
			vertex[3].m_z = zz;
			vertex[3].m_u = minu;
			vertex[3].m_v = minv;

			vertex[4].m_x = maxx;
			vertex[4].m_y = maxy;
			vertex[4].m_z = zz;
			vertex[4].m_u = maxu;
			vertex[4].m_v = maxv;
			
			vertex[5].m_x = minx;
			vertex[5].m_y = maxy;
			vertex[5].m_z = zz;
			vertex[5].m_u = minu;
			vertex[5].m_v = maxv;

			bgfx::setVertexBuffer(0, &vb);
			}
		}
}
namespace bgfxh
{
  BGFXH_STRING fixPath (BGFXH_STRING const & in)
                                                       {
		/// Converts a POSIX path to a windows path and vice versa
		#ifdef __WIN32
			const char from = '/';
			const char to = '\\';
		#else
			const char from = '\\';
			const char to = '/';
		#endif
		BGFXH_STRING out = in;
		for (unsigned int i = 0; i < out.size(); ++i) {
			if (out[i] == from) out[i] = to;
			}
		return out;
		}
}
namespace bgfxh
{
  void readFileRawToString (BGFXH_STRING const & filename, BGFXH_STRING & buff)
                                                                                      {
		std::ifstream fs(fixPath(filename).c_str(), std::ios::in | std::ios::binary);
		if (!fs.is_open()) {
			BGFXH_WARN (false, "Could not open file ", filename );
			return;
			}
		fs.seekg (0, std::ios::end);
		const size_t LEN = fs.tellg();
		fs.seekg (0, std::ios::beg);
		
		buff.resize(LEN);
		fs.read((char *) &buff[0], LEN);
		fs.close();
		return;
		}
}
namespace bgfxh
{
  bgfx::Memory const * readFileRawToBgfxMemory (BGFXH_STRING const & filename)
                                                                                     {
		std::ifstream fs(fixPath(filename).c_str(), std::ios::in | std::ios::binary);
		if (!fs.is_open()) {
			BGFXH_WARN (false, "Could not open file ", filename );
			return NULL;
			}
		fs.seekg (0, std::ios::end);
		const size_t LEN = fs.tellg();
		fs.seekg (0, std::ios::beg);
		
		const bgfx::Memory * mem = bgfx::alloc(LEN);
		fs.read((char *) mem->data, LEN);
		fs.close();
		return mem;
		}
}
namespace bgfxh
{
  bgfx::ProgramHandle loadProgram (char const * vertexShaderFile, char const * fragementShaderFile)
                                                                                                          {
		const bgfx::Memory * vsShaderFileMem = readFileRawToBgfxMemory(vertexShaderFile); //bgfx will auto-dealloc this when done
		if (!vsShaderFileMem) {
			BGFXH_WARN (false, "vertex shader buffer is NULL");
			return BGFX_INVALID_HANDLE;
			}
		bgfx::ShaderHandle vsh = bgfx::createShader(vsShaderFileMem);
		bgfx::setName(vsh, vertexShaderFile);
		
		bgfx::ShaderHandle fsh = BGFX_INVALID_HANDLE;
		if (fragementShaderFile) {
			const bgfx::Memory * fsShaderFileMem = readFileRawToBgfxMemory(fragementShaderFile);
			fsh = bgfx::createShader(fsShaderFileMem);
			bgfx::setName(fsh, fragementShaderFile);
			}

		return bgfx::createProgram(vsh, fsh, true /* destroy shaders when program is destroyed */);
		}
}
namespace bgfxh
{
  bgfx::ProgramHandle loadProgram (BGFXH_STRING const & vertexShaderFile, BGFXH_STRING const & fragmentShaderFile)
                                                                                                                         {
		return loadProgram (vertexShaderFile.c_str(), fragmentShaderFile.c_str());
		}
}
namespace bgfxh
{
  bgfxh::loadProgramCallback * loadProgramCallback::mCallback = NULL;
}
namespace bgfxh
{
  bgfx::ProgramHandle loadProgramCallback::loadProgram (char const * vstag, char const * fstag)
                                                                                                {
			// implement your own loadProgram based on shader tags
			return BGFX_INVALID_HANDLE;
			}
}
namespace bgfxh
{
  bgfx::ProgramHandle loadProgramWCallback (char const * vstag, char const * fstag)
                                                                                         {
		if (!loadProgramCallback::mCallback)
			return loadProgram(bgfxh::shaderSearchPath + vstag + ".bin", bgfxh::shaderSearchPath + fstag + ".bin");
		else
			return loadProgramCallback::mCallback->loadProgram(vstag, fstag);
		}
}
namespace bgfxh
{
  static bx::Vec3 intersectPlanes (bx::Plane const & p1, bx::Plane const & p2, bx::Plane const & p3)
                                                                                                        {
		bx::Vec3 n2xn3 = bx::cross(p1.normal, p3.normal);
		bx::Vec3 n3xn1 = bx::cross(p3.normal, p1.normal);
		bx::Vec3 n1xn2 = bx::cross(p1.normal, p2.normal);

		float denom = bx::dot(p1.normal, n2xn3);

		if (bx::abs(denom) < 1e-6f)
			return bx::Vec3{0.0f, 0.0f, 0.0f};

		bx::Vec3 term1 = bx::mul(n2xn3, -p1.dist);
		bx::Vec3 term2 = bx::mul(n3xn1, -p2.dist);
		bx::Vec3 term3 = bx::mul(n1xn2, -p3.dist);

		bx::Vec3 sum = bx::add(bx::add(term1, term2), term3);

		return bx::mul(sum, 1.0f / denom);
		}
}
namespace bgfxh
{
  void computeFrustumPlanes (float const * m, float * out)
                                                              {
		bx::Plane* outPlanes = (bx::Plane*) out;
		
		#ifdef M
			#define __M_old M
		#endif
		#define M(col,row) m[(col)*4 + (row)]
		
		// LEFT   :  m3 + m0
		outPlanes[0] = bx::Plane(bx::Vec3(M(3,0) + M(0,0), M(3,1) + M(0,1), M(3,2) + M(0,2)), M(3,3) + M(0,3));

		// RIGHT  :  m3 - m0
		outPlanes[1] = bx::Plane(bx::Vec3(M(3,0) - M(0,0), M(3,1) - M(0,1), M(3,2) - M(0,2)), M(3,3) - M(0,3));

		// BOTTOM :  m3 + m1
		outPlanes[2] = bx::Plane(bx::Vec3(M(3,0) + M(1,0), M(3,1) + M(1,1), M(3,2) + M(1,2)), M(3,3) + M(1,3));

		// TOP    :  m3 - m1
		outPlanes[3] = bx::Plane(bx::Vec3(M(3,0) - M(1,0), M(3,1) - M(1,1), M(3,2) - M(1,2)), M(3,3) - M(1,3));

		// NEAR   :  m3 + m2   (OpenGL convention)
		outPlanes[4] = bx::Plane(bx::Vec3(M(3,0) + M(2,0), M(3,1) + M(2,1), M(3,2) + M(2,2)), M(3,3) + M(2,3));

		// FAR    :  m3 - m2
		outPlanes[5] = bx::Plane(bx::Vec3(M(3,0) - M(2,0), M(3,1) - M(2,1), M(3,2) - M(2,2)), M(3,3) - M(2,3));
		
		#undef M
		#ifdef __M_old
			#define M __M_old
		#endif
		
		// Normalize all planes
		for (int i = 0; i < 6; ++i) {
			float x = outPlanes[i].normal.x;
			float y = outPlanes[i].normal.y;
			float z = outPlanes[i].normal.z;
			float d = outPlanes[i].dist;
			
			double invLen = 1.0 / sqrt(x*x + y*y + z*z);
			x *= invLen;
			y *= invLen;
			z *= invLen;
			d *= invLen;
			
			outPlanes[i] = bx::Plane(bx::Vec3(x, y, z), d);
			}
		}
}
namespace bgfxh
{
  void comnputeFustrumPlanesVerts (float const * p, float * out)
                                                                    {
		const bx::Plane* inPlanes = (bx::Plane*) p;
		bx::Vec3* outVec = (bx::Vec3*) out;
		
		const bx::Plane& L = inPlanes[0];
		const bx::Plane& R = inPlanes[1];
		const bx::Plane& B = inPlanes[2];
		const bx::Plane& T = inPlanes[3];
		const bx::Plane& N = inPlanes[4];
		const bx::Plane& F = inPlanes[5];

		// Near
		outVec[0] = intersectPlanes(L, B, N);
		outVec[1] = intersectPlanes(R, B, N);
		outVec[2] = intersectPlanes(R, T, N);
		outVec[3] = intersectPlanes(L, T, N);

		// Far
		outVec[4] = intersectPlanes(L, B, F);
		outVec[5] = intersectPlanes(R, B, F);
		outVec[6] = intersectPlanes(R, T, F);
		outVec[7] = intersectPlanes(L, T, F);		
		}
}
#undef LZZ_INLINE
