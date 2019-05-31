// lumFilter.hh
//

#ifndef LZZ_lumFilter_hh
#define LZZ_lumFilter_hh
#include "bgfxh.h"

///////////////////////////////////////////////////////////////////////
// Lum Filter
// Takes an input texture (or framebuffer), downscales to a 1x1 texture
// and calculates luminance.
// 
// How to use:
// 0. Include! Use #include <bgfxh/bgfxh.h>, #include <bgfxh/lumFilter.h> in a relevent file. Be sure to use #define BGFXH_IMPL *once* to generate an implementation somewhere!
// 1. Create an instance of the lumFilter object ( bgfxh::lumFilter mLumFilter; )
// 2. Set the user parameters to your liking
// 3. Call mLumFilter.init() - this will generate framebuffers and uniforms and load the shaders
// 4. In your rendering loop, call mLumFilter.submit( frameTime ), where frameTime is the time since the last frame in seconds (or just use 1.f/60)
// 5. Use the output as a sampler with mLumFilter.getOutputTexture()
// 
// VIEWS: This filter will consume 5 views
// 
// User Parameters Parameters:
//	bgfx::ViewId viewId; 		// The *first* view id for this. This filter will take up getViewIncrement() incremental views!
//	bgfx::TextureFormat::Enum framebufferTexFormat;	// The texture format for the bloom filter framebuffers. Default is RGBA8
//

#define LZZ_INLINE inline
namespace bgfxh
{
  class lumFilter : public filter
  {
  public:
    bgfx::ProgramHandle m_lumProgram;
    bgfx::ProgramHandle m_lumAvgProgram;
    bgfx::ProgramHandle m_lumAvgOutputProgram;
    bgfx::FrameBufferHandle (m_lumFB) [6];
    bgfx::UniformHandle s_texColor;
    bgfx::UniformHandle s_texLum;
    bgfx::UniformHandle u_lumOffset;
    bgfx::UniformHandle u_screenSize;
    bgfx::UniformHandle u_frameTime;
    bool frameTickTock;
    bool isFirstFrame;
    bool inited;
    bgfx::ViewId viewId;
    bgfx::TextureFormat::Enum framebufferTexFormat;
    lumFilter ();
    ~ lumFilter ();
    bgfx::FrameBufferHandle getOutputFrameBuffer () const;
    int getViewIncrement () const;
  protected:
    void initToZero ();
  public:
    static void setOffsets2x2Lum (bgfx::UniformHandle _handle, uint32_t const _width, uint32_t const _height, float const _texelHalf);
    static void setOffsets4x4Lum (bgfx::UniformHandle _handle, uint32_t const _width, uint32_t const _height, float const _texelHalf);
    void init ();
    void deInit ();
    void submit (bgfx::TextureHandle const & colourBufferIn, float const frameTime = (1.f/60.f));
  };
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
// lumFilter.cpp
//

#define LZZ_INLINE inline
namespace bgfxh
{
  lumFilter::lumFilter ()
                     { initToZero(); }
}
namespace bgfxh
{
  lumFilter::~ lumFilter ()
                      { deInit(); }
}
namespace bgfxh
{
  bgfx::FrameBufferHandle lumFilter::getOutputFrameBuffer () const
                                                              {
		/// Returns the output for the bloom filter
		return frameTickTock ? m_lumFB[5] : m_lumFB[4];
		}
}
namespace bgfxh
{
  int lumFilter::getViewIncrement () const
                                       {
		/// Returns how many views this filter takes
		return 5;
		}
}
namespace bgfxh
{
  void lumFilter::initToZero ()
                           {
		// Sets default vaules for this filter. Used in constructor
		framebufferTexFormat = bgfx::TextureFormat::RGBA8;
		for (int i = 0; i < 6; ++i)
			m_lumFB[i] = BGFX_INVALID_HANDLE;
		
		s_texColor = BGFX_INVALID_HANDLE; // Remember - bgfx::uniformHandles are reference counted by bgfx!
		s_texLum   = BGFX_INVALID_HANDLE;
		u_lumOffset = BGFX_INVALID_HANDLE;
		u_screenSize = BGFX_INVALID_HANDLE;
		u_frameTime  = BGFX_INVALID_HANDLE;
		m_lumProgram = BGFX_INVALID_HANDLE;
		m_lumAvgProgram = BGFX_INVALID_HANDLE;
		m_lumAvgOutputProgram = BGFX_INVALID_HANDLE;
		
		inited = false;
		frameTickTock = 0;
		isFirstFrame = true;
		viewId = 0;
		}
}
namespace bgfxh
{
  void lumFilter::setOffsets2x2Lum (bgfx::UniformHandle _handle, uint32_t const _width, uint32_t const _height, float const _texelHalf)
                                                                                                                                         {
		/*
		* From the BGFX Examples, the following license applies to only this function:
		* Copyright 2011-2018 Branimir Karadzic. All rights reserved.
		* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
		*/
		float offsets[16][4];

		float du = 1.0f/_width;
		float dv = 1.0f/_height;

		uint16_t num = 0;
		for (uint32_t yy = 0; yy < 3; ++yy) {
			for (uint32_t xx = 0; xx < 3; ++xx) {
				offsets[num][0] = (xx - _texelHalf) * du;
				offsets[num][1] = (yy - _texelHalf) * dv;
				++num;
				}
			}

		bgfx::setUniform(_handle, offsets, num);
		}
}
namespace bgfxh
{
  void lumFilter::setOffsets4x4Lum (bgfx::UniformHandle _handle, uint32_t const _width, uint32_t const _height, float const _texelHalf)
                                                                                                                                         {
		/*
		* From the BGFX Examples, the following license applies to only this function:
		* Copyright 2011-2018 Branimir Karadzic. All rights reserved.
		* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
		*/
		float offsets[16][4];

		float du = 1.0f/_width;
		float dv = 1.0f/_height;

		uint16_t num = 0;
		for (uint32_t yy = 0; yy < 4; ++yy) {
			for (uint32_t xx = 0; xx < 4; ++xx) {
				offsets[num][0] = (xx - 1.0f - _texelHalf) * du;
				offsets[num][1] = (yy - 1.0f - _texelHalf) * dv;
				++num;
				}
			}

		bgfx::setUniform(_handle, offsets, num);
		}
}
namespace bgfxh
{
  void lumFilter::init ()
                     {
		/// Creates resources based on User Parameters
		s_texColor  = bgfx::createUniform("s_texColor",  bgfx::UniformType::Sampler);
		s_texLum    = bgfx::createUniform("s_texLum",  bgfx::UniformType::Sampler);
		u_screenSize = bgfx::createUniform("u_screenSize", bgfx::UniformType::Vec4);
		u_frameTime  = bgfx::createUniform("u_frameTime", bgfx::UniformType::Vec4);
		u_lumOffset  = bgfx::createUniform("u_lumOffset", bgfx::UniformType::Vec4, 16);
		
		m_lumFB[0] = bgfx::createFrameBuffer(128, 128, framebufferTexFormat, BGFXH_RT_UV_CLAMP);
		m_lumFB[1] = bgfx::createFrameBuffer( 64,  64, framebufferTexFormat, BGFXH_RT_UV_CLAMP);
		m_lumFB[2] = bgfx::createFrameBuffer( 16,  16, framebufferTexFormat, BGFXH_RT_UV_CLAMP);
		m_lumFB[3] = bgfx::createFrameBuffer(  4,   4, framebufferTexFormat, BGFXH_RT_UV_CLAMP);
		m_lumFB[4] = bgfx::createFrameBuffer(  1,   1, framebufferTexFormat, BGFXH_RT_UV_CLAMP); // Lum Tick
		m_lumFB[5] = bgfx::createFrameBuffer(  1,   1, framebufferTexFormat, BGFXH_RT_UV_CLAMP); // Lum Tock
		bgfx::setName(m_lumFB[0], "Lum0");
		bgfx::setName(m_lumFB[1], "Lum1");
		bgfx::setName(m_lumFB[2], "Lum2");
		bgfx::setName(m_lumFB[3], "Lum3");
		bgfx::setName(m_lumFB[4], "LumOutTick");
		bgfx::setName(m_lumFB[5], "LumOutTock");
		
		#ifdef BGFXH_EMBED_FILTER_SHADERS
			{
			#include "shaders/lum_filter/c/vs_lum.bin.h"
			#include "shaders/lum_filter/c/fs_lum.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_lum_bin),
				BGFXH_EMBEDDED_SHADER(fs_lum_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_lumProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_lum_bin")
											, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_lum_bin")
											, true
											);
			}
			
			{
			#include "shaders/lum_filter/c/vs_lum_avg.bin.h"
			#include "shaders/lum_filter/c/fs_lum_avg.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_lum_avg_bin),
				BGFXH_EMBEDDED_SHADER(fs_lum_avg_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_lumAvgProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_lum_avg_bin")
												, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_lum_avg_bin")
												, true
												);
			}
			{
			#include "shaders/lum_filter/c/vs_lum_avg_output.bin.h"
			#include "shaders/lum_filter/c/fs_lum_avg_output.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_lum_avg_output_bin),
				BGFXH_EMBEDDED_SHADER(fs_lum_avg_output_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_lumAvgOutputProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_lum_avg_output_bin")
													, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_lum_avg_output_bin")
													, true
													);
			}
		#else
			m_lumProgram = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_lum.bin", bgfxh::shaderSearchPath + "fs_lum.bin");
			m_lumAvgProgram = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_lum_avg.bin", bgfxh::shaderSearchPath + "fs_lum_avg.bin");
			m_lumAvgOutputProgram = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_lum_avg_output.bin", bgfxh::shaderSearchPath + "fs_lum_avg_output.bin");
		#endif
		
		BX_CHECK(bgfx::isValid(m_lumProgram), "failed to load shader bgfxh::lumFilter::m_lumProgram! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		BX_CHECK(bgfx::isValid(m_lumAvgProgram), "failed to load shader bgfxh::lumFilter::m_lumAvgProgram! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		BX_CHECK(bgfx::isValid(m_lumAvgOutputProgram), "failed to load shader bgfxh::lumFilter::m_lumAvgOutputProgram! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		
		inited = true;
		}
}
namespace bgfxh
{
  void lumFilter::deInit ()
                       {
		// Frees resources if occupied. bgfxh::destroyhandle will null check
		for (int i = 0; i < 6; ++i)
		bgfxh::destroyHandle (m_lumFB[i]);
		bgfxh::destroyHandle (s_texColor);
		bgfxh::destroyHandle (s_texLum);
		bgfxh::destroyHandle (u_screenSize);
		bgfxh::destroyHandle (u_frameTime);
		
		bgfxh::destroyHandle (m_lumProgram);
		bgfxh::destroyHandle (m_lumAvgProgram);
		bgfxh::destroyHandle (m_lumAvgOutputProgram);
		inited = false;
		}
}
namespace bgfxh
{
  void lumFilter::submit (bgfx::TextureHandle const & colourBufferIn, float const frameTime)
                                                                                                     {
		frameTickTock = !frameTickTock;
		BX_CHECK(inited, "using a bgfxh::lumFilter without calling init()!");
		
		bgfxh::initView2D (viewId + 0, "Luminance", 128, 128, m_lumFB[0]);
		bgfxh::initView2D (viewId + 1, "Downscale Luminance 0", 64, 64, m_lumFB[1]);
		bgfxh::initView2D (viewId + 2, "Downscale Luminance 1", 16, 16, m_lumFB[2]);
		bgfxh::initView2D (viewId + 3, "Downscale Luminance 2",  4,  4, m_lumFB[3]);
		bgfxh::initView2D (viewId + 4, "Downscale Luminance 3",  1,  1, frameTickTock ? m_lumFB[4] : m_lumFB[5]);
			
		const bgfx::RendererType::Enum renderer = bgfx::getRendererType();
		const float _texelHalf = (bgfx::RendererType::Direct3D9 == renderer) ? 0.5f : 0.0f;
	
		bgfxh::lumFilter::setOffsets2x2Lum(u_lumOffset, 128, 128, _texelHalf);
		bgfx::setTexture(SAMPLER_COLOR, s_texColor, colourBufferIn);
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		bgfxh::fullscreenQuad(128.0f, 128.0f);
		bgfx::submit(viewId + 0, m_lumProgram);
		
		// Downscale luminance 0.
		bgfxh::lumFilter::setOffsets4x4Lum(u_lumOffset, 128, 128, _texelHalf);
		bgfx::setTexture(SAMPLER_COLOR, s_texColor, bgfx::getTexture(m_lumFB[0]) );
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		bgfxh::fullscreenQuad(64.0f, 64.0f);
		bgfx::submit(viewId + 1, m_lumAvgProgram);

		// Downscale luminance 1.
		bgfxh::lumFilter::setOffsets4x4Lum(u_lumOffset, 64, 64, _texelHalf);
		bgfx::setTexture(SAMPLER_COLOR, s_texColor, bgfx::getTexture(m_lumFB[1]) );
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		bgfxh::fullscreenQuad(16.0f, 16.0f);
		bgfx::submit(viewId + 2, m_lumAvgProgram);

		// Downscale luminance 2.
		bgfxh::lumFilter::setOffsets4x4Lum(u_lumOffset, 16, 16, _texelHalf);
		bgfx::setTexture(SAMPLER_COLOR, s_texColor, bgfx::getTexture(m_lumFB[2]) );
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		bgfxh::fullscreenQuad(4.0f, 4.0f);
		bgfx::submit(viewId + 3, m_lumAvgProgram);

		// Downscale luminance 3.
		bgfxh::lumFilter::setOffsets4x4Lum(u_lumOffset, 4, 4, _texelHalf); // This is a 1x1 buffer
		bgfx::setTexture(SAMPLER_COLOR, s_texColor, bgfx::getTexture(m_lumFB[3]) );
		bgfx::setTexture(SAMPLER_LUM  , s_texLum, bgfx::getTexture(frameTickTock ? m_lumFB[5] : m_lumFB[4]) );
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		bgfxh::fullscreenQuad(1.0f, 1.0f);
		
		float ftarr[4] = { frameTime, 0.0f, 0.0f, 0.0f };
		bgfx::setUniform(u_frameTime, ftarr);
		
		if (isFirstFrame)
			bgfx::submit(viewId + 4, m_lumAvgProgram);
		else
			bgfx::submit(viewId + 4, m_lumAvgOutputProgram);
		isFirstFrame = false;
		}
}
#undef LZZ_INLINE
#endif //BGFXH_IMPL
