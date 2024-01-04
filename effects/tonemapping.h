// tonemapping.hh
//

#ifndef LZZ_tonemapping_hh
#define LZZ_tonemapping_hh
///////////////////////////////////////////////////////////////////////
// Tonemapping Filter
// 
// Takes an input linear colour buffer and a luminance value and outputs an expopsure adjusted and tonemapped output
// This filter uses the ACES Filmic tone mapping curve
//
// This filter can also accept up to 4 other colour buffers and additively combine them with the colour buffer. So you can use this to merge the output of a bloom filter, SSR filter, Ambient Occulsion, etc, all in one pass! 
//
// How to use:
// 0. Include! Use #include <bgfxh/bgfxh.h>, #include <bgfxh/tonemappingEffect.h> in a relevent file. Be sure to use #define BGFXH_IMPL *once* to generate an implementation somewhere!
// 1. Create an instance of the tonemappingEffect object ( bgfxh::tonemappingEffect mTonemappingFilter
// 2. Set the user parameters to your liking. Use mTonemappingFilter.setSize(width, height);
// 3. Call tonemappingEffect.init() - this will generate framebuffers and uniforms and load the shaders
// 4. In your rendering loop, call mTonemappingFilter.submit()
// 5. Use the output as a sampler with mTonemappingFilter.getOutputTexture()
// 
// How to blend multiple filters together in this stage
//	mTonemappingFilter.maxAdditonalSamplerSlots = 2; // <-- blend in 2 more channels. Must be set before init()!! Which shader is loaded depends on this value
//
//  mTonemappingFilter.setExtraComponent (0, bloomFilter.getOutputTexture(), 1.0f, 0.0f); // Add a small bloom in slot 0 and add
//  mTonemappingFilter.setExtraComponent (1, ambientOcclusionFilter.getOutputTexture(), 0.0f, 0.8f); // Add a ambientOcclusionFilter to slot 1 and multiply rgb by value
//  mTonemappingFilter.submit ();
//
// How to render to backbuffer (default behaviour)
//	mTonemappingFilter.renderToBackbuffer = true;
//  mTonemappingFilter.setSize (backbufferWidth, backbufferHeight);
//  mTonemappingFilter.init();

// VIEWS: This filter will consume 1 + 2*nBloomBlurPasses views
// 
// User Parameters:
//	bgfx::ViewId viewId;							// Must be set to see anything!
//	uint32_t width, height;							// Width and height of the filter
//	bool renderToBackbuffer;						// Set to true to autogenerate a framebuffer and render to it
//	bgfx::TextureFormat::Enum framebufferTexFormat;	// Texture format for said framebuffer
//  uint32_t maxAdditonalSamplerSlots;				// The number of additional sampler slots for blending. Default is zero

#define LZZ_INLINE inline
namespace bgfxh
{
  class tonemappingEffect : public renderJob
  {
  public:
    bgfx::FrameBufferHandle mOutputFB;
    bgfx::UniformHandle s_texColor;
    bgfx::UniformHandle s_texLum;
    bgfx::UniformHandle (s_texFilterExtra) [4];
    bgfx::UniformHandle u_weightsAdd;
    bgfx::UniformHandle u_weightsMul;
    bgfx::TextureHandle (textureToCombine) [4];
    bgfx::ProgramHandle m_tonemappingProgram;
    float (additiveWeights) [4];
    float (multiplicitiveWeights) [4];
    bool inited;
    bgfx::ViewId viewId;
    bgfx::TextureFormat::Enum framebufferTexFormat;
    uint32_t width;
    uint32_t height;
    uint32_t maxAdditonalSamplerSlots;
    bool renderToBackbuffer;
    tonemappingEffect ();
    ~ tonemappingEffect ();
    void setSize (uint32_t const _width, uint32_t const _height);
    bgfx::FrameBufferHandle getOutputFrameBuffer () const;
    int getViewIncrement () const;
    void setExtraComponent (uint32_t slot, bgfx::TextureHandle const texture, float additiveWeight, float multiplicitveWeight);
    void initToZero ();
    void init ();
    void deInit ();
    void submit (bgfx::TextureHandle const colourBufferIn, bgfx::TextureHandle const lumBufferIn);
  };
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
#ifndef BGFXH_DOUBLE_GUARD_effects_tonemapping
#define BGFXH_DOUBLE_GUARD_effects_tonemapping
// tonemapping.cpp
//

#define LZZ_INLINE inline
namespace bgfxh
{
  tonemappingEffect::tonemappingEffect ()
                             { initToZero(); }
}
namespace bgfxh
{
  tonemappingEffect::~ tonemappingEffect ()
                              { deInit(); }
}
namespace bgfxh
{
  void tonemappingEffect::setSize (uint32_t const _width, uint32_t const _height)
                                                                     {
		width = _width;
		height = _height; 
		}
}
namespace bgfxh
{
  bgfx::FrameBufferHandle tonemappingEffect::getOutputFrameBuffer () const
                                                              { return mOutputFB; }
}
namespace bgfxh
{
  int tonemappingEffect::getViewIncrement () const
                                      { return 1; }
}
namespace bgfxh
{
  void tonemappingEffect::setExtraComponent (uint32_t slot, bgfx::TextureHandle const texture, float additiveWeight, float multiplicitveWeight)
                                                                                                                                   {
		BGFXH_ASSERT (slot < 4, "Only 4 tonemapping attachments are supported!");
		BGFXH_ASSERT (slot < maxAdditonalSamplerSlots, "tonemapping: maxAdditonalSamplerSlots must be set to the maximum number of channels you wish to use before you call init()!");
		
		textureToCombine[slot] = texture;
		additiveWeights[slot] = additiveWeight;
		multiplicitiveWeights[slot] = multiplicitveWeight;
		}
}
namespace bgfxh
{
  void tonemappingEffect::initToZero ()
                           {
		mOutputFB = BGFX_INVALID_HANDLE;
		s_texColor = BGFX_INVALID_HANDLE;
		s_texLum = BGFX_INVALID_HANDLE;
		m_tonemappingProgram = BGFX_INVALID_HANDLE;
		
		for (unsigned int i = 0; i < 4; ++i) {
			s_texFilterExtra[i] = BGFX_INVALID_HANDLE;
			textureToCombine[i] = BGFX_INVALID_HANDLE;
			additiveWeights[i] = 0.f;
			multiplicitiveWeights[i] = 0.f;
			}
		u_weightsAdd = BGFX_INVALID_HANDLE;
		u_weightsMul = BGFX_INVALID_HANDLE;
		viewId = 0;
		maxAdditonalSamplerSlots = 0;
		framebufferTexFormat = bgfx::TextureFormat::RGBA8;
		width = bgfxh::screenWidth;
		height = bgfxh::screenHeight;
		renderToBackbuffer = true;
		inited = false;
		}
}
namespace bgfxh
{
  void tonemappingEffect::init ()
                     {
		BGFXH_ASSERT(!inited, "double initialisation");
		
		if (!renderToBackbuffer) {
			mOutputFB = bgfx::createFrameBuffer(width, height, framebufferTexFormat, BGFXH_RT_UV_CLAMP);
			bgfx::setName(mOutputFB, "bgfxh::tonemappingEffect::mOutputFB");
			}
		s_texColor  = bgfx::createUniform("s_texColor",  bgfx::UniformType::Sampler);
		s_texLum    = bgfx::createUniform("s_texLum",    bgfx::UniformType::Sampler);
		
		u_weightsAdd =  bgfx::createUniform("u_weightsAdd", bgfx::UniformType::Vec4);
		u_weightsMul =  bgfx::createUniform("u_weightsMul", bgfx::UniformType::Vec4);
		
		for (unsigned int i = 0; i < 4; ++i) {
			char buf[32];
			snprintf(buf, 31, "s_texFilterExtra%i", i);
			s_texFilterExtra[i] = bgfx::createUniform(buf, bgfx::UniformType::Sampler);
			}
			
		#ifdef BGFXH_EMBED_EFFECT_SHADERS
			if (maxAdditonalSamplerSlots == 0) {
			#include "../shaders/tonemapping/c/vs_tonemapping.bin.h"
			#include "../shaders/tonemapping/c/fs_tonemapping.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_tonemapping_bin),
				BGFXH_EMBEDDED_SHADER(fs_tonemapping_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_tonemappingProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_tonemapping_bin")
														, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_tonemapping_bin")
														, true
														);
			}
			if (maxAdditonalSamplerSlots == 1) {
			#include "../shaders/tonemapping/c/vs_tonemapping_ch1.bin.h"
			#include "../shaders/tonemapping/c/fs_tonemapping_ch1.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_tonemapping_ch1_bin),
				BGFXH_EMBEDDED_SHADER(fs_tonemapping_ch1_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_tonemappingProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_tonemapping_ch1_bin")
														, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_tonemapping_ch1_bin")
														, true
														);
			}
			if (maxAdditonalSamplerSlots == 2) {
			#include "../shaders/tonemapping/c/vs_tonemapping_ch2.bin.h"
			#include "../shaders/tonemapping/c/fs_tonemapping_ch2.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_tonemapping_ch2_bin),
				BGFXH_EMBEDDED_SHADER(fs_tonemapping_ch2_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_tonemappingProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_tonemapping_ch2_bin")
														, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_tonemapping_ch2_bin")
														, true
														);
			}
			if (maxAdditonalSamplerSlots == 3) {
			#include "../shaders/tonemapping/c/vs_tonemapping_ch3.bin.h"
			#include "../shaders/tonemapping/c/fs_tonemapping_ch3.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_tonemapping_ch3_bin),
				BGFXH_EMBEDDED_SHADER(fs_tonemapping_ch3_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_tonemappingProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_tonemapping_ch3_bin")
														, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_tonemapping_ch3_bin")
														, true
														);
			}
			if (maxAdditonalSamplerSlots == 4) {
			#include "../shaders/tonemapping/c/vs_tonemapping_ch4.bin.h"
			#include "../shaders/tonemapping/c/fs_tonemapping_ch4.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_tonemapping_ch4_bin),
				BGFXH_EMBEDDED_SHADER(fs_tonemapping_ch4_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_tonemappingProgram = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_tonemapping_ch4_bin")
														, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_tonemapping_ch4_bin")
														, true
														);
			}
		#else
		if (maxAdditonalSamplerSlots) {
			char bufa[64];
			char bufb[64];
			snprintf (bufa, 63, "vs_tonemapping_ch%i.bin", maxAdditonalSamplerSlots);
			snprintf (bufb, 63, "fs_tonemapping_ch%i.bin", maxAdditonalSamplerSlots);
			m_tonemappingProgram = bgfxh::loadProgram(bgfxh::shaderSearchPath + bufa, bgfxh::shaderSearchPath + bufb);
			}
		else
			m_tonemappingProgram = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_tonemapping.bin", bgfxh::shaderSearchPath + "fs_tonemapping.bin");
		#endif
		BGFXH_ASSERT(bgfx::isValid(m_tonemappingProgram), "failed to load shader bgfxh::tonemappingEffect::m_tonemappingProgram! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		inited = true;
		}
}
namespace bgfxh
{
  void tonemappingEffect::deInit ()
                       {
		bgfxh::destroyHandle(mOutputFB);
		bgfxh::destroyHandle(s_texColor);
		bgfxh::destroyHandle(s_texLum);
		bgfxh::destroyHandle(m_tonemappingProgram);
		
		for (unsigned int i = 0; i < 4; ++i) {
			bgfxh::destroyHandle(s_texFilterExtra[i]);
			bgfxh::destroyHandle(textureToCombine[i]);
			additiveWeights[i] = 0.f;
			multiplicitiveWeights[i] = 0.f;
			}
		bgfxh::destroyHandle(u_weightsAdd);
		bgfxh::destroyHandle(u_weightsMul);
		inited = false;
		}
}
namespace bgfxh
{
  void tonemappingEffect::submit (bgfx::TextureHandle const colourBufferIn, bgfx::TextureHandle const lumBufferIn)
                                                                                                      {
		bgfxh::initView2D (viewId, "Tonemapping", width, height, mOutputFB);
		
		bgfx::setTexture(bgfxh::SAMPLER_COLOR, s_texColor, colourBufferIn );
		bgfx::setTexture(bgfxh::SAMPLER_LUM, s_texLum, lumBufferIn );
		bgfx::setTexture(bgfxh::SAMPLER_TONEMAPING_EXTRA0, s_texFilterExtra[0], textureToCombine[0] );
		bgfx::setTexture(bgfxh::SAMPLER_TONEMAPING_EXTRA1, s_texFilterExtra[1], textureToCombine[1] );
		bgfx::setTexture(bgfxh::SAMPLER_TONEMAPING_EXTRA2, s_texFilterExtra[2], textureToCombine[2] );
		bgfx::setTexture(bgfxh::SAMPLER_TONEMAPING_EXTRA3, s_texFilterExtra[3], textureToCombine[3] );
		
		bgfx::setUniform(u_weightsAdd, additiveWeights);
		bgfx::setUniform(u_weightsMul, multiplicitiveWeights);
			
		for (unsigned int i = 0; i < 4; ++i) {
			// Unset everything, as they may not be valid next frame
			// The user (you!) have to set these every frame before submit
			textureToCombine[i] = BGFX_INVALID_HANDLE;
			additiveWeights[i] = 0.f;
			multiplicitiveWeights[i] = 0.f;
			}
		
		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		bgfxh::fullscreenQuad(width, height);
		bgfx::submit(viewId, m_tonemappingProgram);
		}
}
#undef LZZ_INLINE
#endif //BGFXH_DOUBLE_GUARD_effects_tonemapping
#endif //BGFXH_IMPL
