// bloom.hh
//

#ifndef LZZ_bloom_hh
#define LZZ_bloom_hh
#include "../bgfxh.h"

///////////////////////////////////////////////////////////////////////
// Bloom Filter
// 
// How to use:
// 0. Include! Use #include <bgfxh/bgfxh.h>, #include <bgfxh/bloomRenderJob.h> in a relevent file. Be sure to use #define BGFXH_IMPL *once* to generate an implementation somewhere!
// 1. Create an instance of the bloomRenderJob object ( bgfxh::bloomRenderJob mBloomFilter
// 2. Set the user parameters to your liking
// 3. Call mBloomFilter.init() - this will generate framebuffers and uniforms and load the shaders
// 4. In your rendering loop, call mBloomFilter.submit( textureToBloom, { lumTextureIfUsingLum } )
// 5. Use the output as a sampler with mBloomFilter.getOutputTexture()
// 
// VIEWS: This filter will consume 1 + 2*nBloomBlurPasses views
// 
// User Parameters:
//	uint32_t bloomWidth;		// The width of the bloom filter. For better performance this can be half or even a quater of the size of your input texture
//	uint32_t bloomHeight;		// Height
//	uint32_t nBloomBlurPasses;	// The number of times a gaussian blur is applied to the bloom
//	bgfx::ViewId viewId; 		// The *first* view id for this. This filter will take up getViewIncrement() incremental views!
//	bgfx::TextureFormat::Enum framebufferTexFormat;	// The texture format for the bloom filter framebuffers. Default is RGBA8
//	bool useLum;				// Calcualte bloom threshold based on lumance? If set to true
//

#define LZZ_INLINE inline
namespace bgfxh
{
  class bloomRenderJob : public renderJob
  {
  public:
    bgfx::ProgramHandle m_bloomExtractProgram;
    bgfx::ProgramHandle (m_programBloomBlur) [2];
    bgfx::FrameBufferHandle (m_bloomFB) [2];
    bgfx::UniformHandle s_texColor;
    bgfx::UniformHandle s_texLum;
    bgfx::UniformHandle u_screenSize;
    bool inited;
    uint32_t bloomWidth;
    uint32_t bloomHeight;
    uint32_t nBloomBlurPasses;
    bgfx::ViewId viewId;
    bgfx::TextureFormat::Enum framebufferTexFormat;
    bool useLum;
    bloomRenderJob ();
    ~ bloomRenderJob ();
    bgfx::FrameBufferHandle getOutputFrameBuffer () const;
    int getViewIncrement () const;
  protected:
    void initToZero ();
  public:
    void setSize (uint32_t const _bloomWidth, uint32_t const _bloomHeight);
    void init ();
    void deInit ();
  protected:
    void submit_common (bgfx::TextureHandle const & colourBufferIn, bgfx::TextureHandle const & lumBufferIn);
  public:
    void submit (bgfx::TextureHandle const & colourBufferIn, bgfx::TextureHandle const & lumBufferIn);
    void submit (bgfx::TextureHandle const & colourBufferIn);
  };
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
// bloom.cpp
//

#define LZZ_INLINE inline
namespace bgfxh
{
  bloomRenderJob::bloomRenderJob ()
                          { initToZero(); }
}
namespace bgfxh
{
  bloomRenderJob::~ bloomRenderJob ()
                           { deInit(); }
}
namespace bgfxh
{
  bgfx::FrameBufferHandle bloomRenderJob::getOutputFrameBuffer () const
                                                              {
		/// Returns the output for the bloom filter
		return m_bloomFB[1];
		}
}
namespace bgfxh
{
  int bloomRenderJob::getViewIncrement () const
                                       {
		/// Returns how many views this filter takes
		return 1 + nBloomBlurPasses*2;
		}
}
namespace bgfxh
{
  void bloomRenderJob::initToZero ()
                           {
		// Sets default vaules for this filter. Used in constructor
		bloomWidth  = 512;
		bloomHeight = 512;
		nBloomBlurPasses = 1;
		framebufferTexFormat = bgfx::TextureFormat::RGBA8;
		m_bloomExtractProgram = BGFX_INVALID_HANDLE;
		m_programBloomBlur[0] = BGFX_INVALID_HANDLE;
		m_programBloomBlur[1] = BGFX_INVALID_HANDLE;
		m_bloomFB[0] = BGFX_INVALID_HANDLE;
		m_bloomFB[1] = BGFX_INVALID_HANDLE;
		
		s_texColor = BGFX_INVALID_HANDLE; // Remember - bgfx::uniformHandles are reference counted by bgfx!
		s_texLum = BGFX_INVALID_HANDLE;
		u_screenSize = BGFX_INVALID_HANDLE;
		
		useLum = true;
		inited = false;
		viewId = 0;
		}
}
namespace bgfxh
{
  void bloomRenderJob::setSize (uint32_t const _bloomWidth, uint32_t const _bloomHeight)
                                                                               {
		bloomWidth = _bloomWidth;
		bloomHeight = _bloomHeight; 
		}
}
namespace bgfxh
{
  void bloomRenderJob::init ()
                     {
		/// Creates resources based on User Parameters
		m_bloomFB[0] = bgfx::createFrameBuffer(bloomWidth, bloomHeight, framebufferTexFormat, BGFXH_RT_UV_CLAMP); // Bloom Tick
		m_bloomFB[1] = bgfx::createFrameBuffer(bloomWidth, bloomHeight, framebufferTexFormat, BGFXH_RT_UV_CLAMP); // Bloom Tock
		bgfx::setName(m_bloomFB[0], "Bloom Tick");
		bgfx::setName(m_bloomFB[1], "Bloom Tock");
		s_texColor  = bgfx::createUniform("s_texColor",  bgfx::UniformType::Sampler);
		s_texLum    = bgfx::createUniform("s_texLum",    bgfx::UniformType::Sampler);
		u_screenSize = bgfx::createUniform("u_screenSize", bgfx::UniformType::Vec4);
		
		#ifdef BGFXH_EMBED_RENDER_JOB_SHADERS
			if (useLum) {
			#include "../shaders/bloom/c/vs_bloom_brightpass_lum.bin.h"
			#include "../shaders/bloom/c/fs_bloom_brightpass_lum.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_bloom_brightpass_lum_bin),
				BGFXH_EMBEDDED_SHADER(fs_bloom_brightpass_lum_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_bloomExtractProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_bloom_brightpass_lum_bin")
														, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_bloom_brightpass_lum_bin")
														, true
														);
			}
			else {
			#include "../shaders/bloom/c/vs_bloom_brightpass.bin.h"
			#include "../shaders/bloom/c/fs_bloom_brightpass.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_bloom_brightpass_bin),
				BGFXH_EMBEDDED_SHADER(fs_bloom_brightpass_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_bloomExtractProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_bloom_brightpass_bin")
														, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_bloom_brightpass_bin")
														, true
														);
			}
			
			
			{
			#include "../shaders/bloom/c/vs_bloom_blur_hz.bin.h"
			#include "../shaders/bloom/c/fs_bloom_blur_hz.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_bloom_blur_hz_bin),
				BGFXH_EMBEDDED_SHADER(fs_bloom_blur_hz_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programBloomBlur[0] = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_bloom_blur_hz_bin")
													, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_bloom_blur_hz_bin")
													, true
													);
			}
			{
			#include "../shaders/bloom/c/vs_bloom_blur_vt.bin.h"
			#include "../shaders/bloom/c/fs_bloom_blur_vt.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_bloom_blur_vt_bin),
				BGFXH_EMBEDDED_SHADER(fs_bloom_blur_vt_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programBloomBlur[1] = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_bloom_blur_vt_bin")
													, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_bloom_blur_vt_bin")
													, true
													);
			}
		#else
			if (useLum)
				m_bloomExtractProgram = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_bloom_brightpass_lum.bin", bgfxh::shaderSearchPath + "fs_bloom_brightpass_lum.bin");
			else
				m_bloomExtractProgram = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_bloom_brightpass.bin", bgfxh::shaderSearchPath + "fs_bloom_brightpass.bin");
			m_programBloomBlur[0] = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_bloom_blur_hz.bin", bgfxh::shaderSearchPath + "fs_bloom_blur_hz.bin");
			m_programBloomBlur[1] = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_bloom_blur_vt.bin", bgfxh::shaderSearchPath + "fs_bloom_blur_vt.bin");
		#endif
			
		BGFXH_CHECK(bgfx::isValid(m_bloomExtractProgram), "failed to load shader bgfxh::bloomRenderJob::m_bloomExtractProgram! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		BGFXH_CHECK(bgfx::isValid(m_programBloomBlur[0]), "failed to load shader bgfxh::bloomRenderJob::m_programBloomBlur[0]! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		BGFXH_CHECK(bgfx::isValid(m_programBloomBlur[1]), "failed to load shader bgfxh::bloomRenderJob::m_programBloomBlur[1]! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		
		//fmt::println ("init! {} {} {} ", bgfx::isValid(m_bloomExtractProgram), bgfx::isValid(m_programBloomBlur[0]), bgfx::isValid(m_programBloomBlur[1]));
		//abort ();
		inited = true;
		}
}
namespace bgfxh
{
  void bloomRenderJob::deInit ()
                       {
		// Frees resources if occupied. bgfxh::destroyhandle will null check
		bgfxh::destroyHandle (m_bloomFB[0]);
		bgfxh::destroyHandle (m_bloomFB[1]);
		bgfxh::destroyHandle (s_texColor);
		bgfxh::destroyHandle (s_texLum);
		bgfxh::destroyHandle (u_screenSize);
		
		bgfxh::destroyHandle (m_bloomExtractProgram);
		bgfxh::destroyHandle (m_programBloomBlur[0]);
		bgfxh::destroyHandle (m_programBloomBlur[1]);
		inited = false;
		}
}
namespace bgfxh
{
  void bloomRenderJob::submit_common (bgfx::TextureHandle const & colourBufferIn, bgfx::TextureHandle const & lumBufferIn)
                                                                                                                 {
		bgfxh::initView2D (viewId, "Bloom Extract", bloomWidth, bloomHeight, m_bloomFB[1]);
		for (uint32_t i = 0; i < nBloomBlurPasses; ++i) {
			bgfxh::initView2D (viewId+1+i*2, "Bloom Blur Horz", bloomWidth, bloomHeight, m_bloomFB[0]);
			bgfxh::initView2D (viewId+2+i*2, "Bloom Blur Vert", bloomWidth, bloomHeight, m_bloomFB[1]);
			}
			
		float screenSize[4] = { float(bloomWidth), float(bloomHeight), float(bgfxh::screenWidth), float(bgfxh::screenHeight) };
		bgfx::setUniform(u_screenSize, screenSize);
			
		// Extract pass      
		bgfx::setTexture(bgfxh::SAMPLER_COLOR, s_texColor, colourBufferIn );
		if (useLum && bgfx::isValid(lumBufferIn)) {
			bgfx::setTexture(bgfxh::SAMPLER_LUM, s_texLum, lumBufferIn );
			}
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		bgfxh::fullscreenQuad(bloomWidth, bloomHeight);
		bgfx::submit(viewId, m_bloomExtractProgram);
		
		// Blur passes
		for (unsigned int i = 0; i < nBloomBlurPasses; ++i) {
			bgfx::setTexture(bgfxh::SAMPLER_COLOR , s_texColor, bgfx::getTexture(m_bloomFB[1]) );
			bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
			bgfx::setUniform(u_screenSize, screenSize);
			bgfxh::fullscreenQuad(bloomWidth, bloomHeight);
			bgfx::submit(viewId + 1 + i*2, m_programBloomBlur[0]);
			
			bgfx::setTexture(bgfxh::SAMPLER_COLOR , s_texColor, bgfx::getTexture(m_bloomFB[0]) );
			bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
			bgfx::setUniform(u_screenSize, screenSize);
			bgfxh::fullscreenQuad(bloomWidth, bloomHeight);
			bgfx::submit(viewId + 2 + i*2, m_programBloomBlur[1]);
			}
		}
}
namespace bgfxh
{
  void bloomRenderJob::submit (bgfx::TextureHandle const & colourBufferIn, bgfx::TextureHandle const & lumBufferIn)
                                                                                                          {
		BGFXH_CHECK(useLum, "bgfxh::bloomRenderJob: submiting with lum buffer when configured to not use one! Set useLum to true before init()!");
		BGFXH_CHECK(inited, "using a bgfxh::bloomRenderJob without calling init()!");
		
		// Bloom with lum
		submit_common (colourBufferIn, lumBufferIn);
		}
}
namespace bgfxh
{
  void bloomRenderJob::submit (bgfx::TextureHandle const & colourBufferIn)
                                                                 {
		BGFXH_CHECK(!useLum, "bgfxh::bloomRenderJob: submiting without a lum buffer!");
		BGFXH_CHECK(inited, "using a bgfxh::bloomRenderJob without calling init()!");
		
		// Bloom without lum
		submit_common (colourBufferIn, BGFX_INVALID_HANDLE);
		}
}
#undef LZZ_INLINE
#endif //BGFXH_IMPL
