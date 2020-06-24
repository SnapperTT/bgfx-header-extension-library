// guassianBlur.hh
//

#ifndef LZZ_guassianBlur_hh
#define LZZ_guassianBlur_hh
#include "../bgfxh.h"

///////////////////////////////////////////////////////////////////////
// Bloom Filter
// 
// How to use:
// 0. Include! Use #include <bgfxh/bgfxh.h>, #include <bgfxh/guassianBlurEffect.h> in a relevent file. Be sure to use #define BGFXH_IMPL *once* to generate an implementation somewhere!
// 1. Create an instance of the guassianBlurEffect object ( bgfxh::guassianBlurEffect mBlurJob
// 2. Set the user parameters to your liking
// 3. Call mBlurJob.init() - this will generate framebuffers and uniforms and load the shaders
// 4. In your rendering loop, call mBlurJob.submit( textureToBlur )
// 5. Use the output as a sampler with mBlurJob.getOutputTexture()
// 
// VIEWS: This filter will consume 1 + 2*nBlurPasses views
// 
// User Parameters:
//	uint32_t blurWidth;		// The width of the blur. For better performance this can be half or even a quater of the size of your input texture
//	uint32_t blurHeight;	// Height
//	uint32_t nBlurPasses;	// The number of times a gaussian blur is applied
//	uint32_t kernalSize;	// The size of the kernal in pixels
//	double sigma;			// The sigma value for the guassian function. If set to zero this will automatically pick one that will fit the kernal
//	bgfx::ViewId viewId; 	// The *first* view id for this. This filter will take up getViewIncrement() incremental views!
//	bgfx::TextureFormat::Enum framebufferTexFormat;	// The texture format for the bloom filter framebuffers. Default is RGBA8
//
//	Free functions:
//	double guassian (sigma, x)	// Returns the value of the guassian function with specified parameters
// 	double getGuassianSigmaFromKernalSize (double kernalSz, double thresh = 1.0/256.0)	// Calcualtes a suitable sigma such that guassian(sigma, kernalSz) = thresh
// 	double calcGuassianBlurWeights (const unsigned int kernalSz, double sigma, double * weightsOut, double * offsetsOut) // See documentation in this file
//
#define LZZ_INLINE inline
namespace bgfxh
{
  double guassian (double sigma, double x);
}
namespace bgfxh
{
  double getGuassianSigmaFromKernalSize (double kernalSz, double thresh = 1.0/256.0);
}
namespace bgfxh
{
  void calcGuassianBlurWeights (unsigned int const kernalSz, double sigma, double * weightsOut, double * offsetsOut);
}
namespace bgfxh
{
  class guassianBlurEffect : public renderJob
  {
  public:
    bgfx::ProgramHandle (m_programBlur) [2];
    bgfx::FrameBufferHandle (m_blurFB) [2];
    bgfx::UniformHandle s_texColor;
    bgfx::UniformHandle u_blurParameters;
    bgfx::UniformHandle u_screenSize;
    bool inited;
    uint32_t blurWidth;
    uint32_t blurHeight;
    uint32_t nBlurPasses;
    uint32_t kernalSize;
    double sigma;
    bgfx::ViewId viewId;
    bgfx::TextureFormat::Enum framebufferTexFormat;
    guassianBlurEffect ();
    ~ guassianBlurEffect ();
    bgfx::FrameBufferHandle getOutputFrameBuffer () const;
    int getViewIncrement () const;
  protected:
    void initToZero ();
  public:
    void setSize (uint32_t const _blurWidth, uint32_t const _blurHeight);
    void init ();
    void deInit ();
  protected:
    void submit_common (bgfx::TextureHandle const & colourBufferIn);
  public:
    void submit (bgfx::TextureHandle const & colourBufferIn);
  };
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
#ifndef BGFXH_DOUBLE_GUARD_effects_guassianBlur
#define BGFXH_DOUBLE_GUARD_effects_guassianBlur
// guassianBlur.cpp
//

#define MAX_SAMPLES 8
#define LZZ_INLINE inline
namespace bgfxh
{
  double guassian (double sigma, double x)
                                         {
	constexpr double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280; // lol digits
	#if defined(__clang__)
		const double a = sqrt(1.0/(2.0*pi)); //sqrt isn't constexpr according to clang...
	#else
		constexpr double a = sqrt(1.0/(2.0*pi)); //sqrt isn't constexpr according to clang...
	#endif
	const double sigmaRecip = 1.0/sigma;
	return sigmaRecip*a*exp(-0.5*x*x*sigmaRecip*sigmaRecip);
	}
}
namespace bgfxh
{
  double getGuassianSigmaFromKernalSize (double kernalSz, double thresh)
                                                                                   {
	double FWTM = 2*sqrt(2*log(1.0/thresh));
	double sigmaZero = max(1.0,kernalSz)/(FWTM/2);
	double sigmaOne = sigmaZero;
	for (int i = 0; i < 6; ++i) { //6 steps is stupidly close
		const double guassianZero = guassian(sigmaOne, 0);
		FWTM = 2*sqrt(2*log(guassianZero/thresh));
		sigmaOne = max(1.0,kernalSz)/(FWTM/2);
		}
	return sigmaOne;
	}
}
namespace bgfxh
{
  void calcGuassianBlurWeights (unsigned int const kernalSz, double sigma, double * weightsOut, double * offsetsOut)
                                                                                                                   {
	double weights[kernalSz+1];
	for (unsigned int i = 0; i < kernalSz; ++i) {
		weights[i] = guassian(sigma, i); // This is close to normalised
		}
	// Renormalise
	double sum = weights[0];
	for (unsigned int i = 1; i < kernalSz; ++i) {
		sum += 2.0*weights[i];
		}
	sum = 1.0/sum;
	for (unsigned int i = 0; i < kernalSz; ++i) {
		weights[i]*=sum;
		}
	weights[kernalSz] = 0;

	//double weight2[kernalSz/2 + 1];
	//double offset2[kernalSz/2 + 1];
	double * weight2 = weightsOut;
	double * offset2 = offsetsOut;
	weight2[0] = weights[0];
	offset2[0] = 0.0;
	for (unsigned int i = 1; i < kernalSz; i+=2) {
		weight2[i/2+1] = weights[i] + weights[i+1];
		offset2[i/2+1] = (i*weights[i] + (i+1)*weights[i+1])/weight2[i/2+1];
		}
	}
}
namespace bgfxh
{
  guassianBlurEffect::guassianBlurEffect ()
                              { initToZero(); }
}
namespace bgfxh
{
  guassianBlurEffect::~ guassianBlurEffect ()
                               { deInit(); }
}
namespace bgfxh
{
  bgfx::FrameBufferHandle guassianBlurEffect::getOutputFrameBuffer () const
                                                              {
		/// Returns the output for the bloom filter
		return m_blurFB[1];
		}
}
namespace bgfxh
{
  int guassianBlurEffect::getViewIncrement () const
                                       {
		/// Returns how many views this filter takes
		return nBlurPasses*2;
		}
}
namespace bgfxh
{
  void guassianBlurEffect::initToZero ()
                           {
		// Sets default vaules for this filter. Used in constructor
		blurWidth  = 512;
		blurHeight = 512;
		nBlurPasses = 1;
		kernalSize = 9;
		sigma = 0;
		framebufferTexFormat = bgfx::TextureFormat::RGBA16F;
		m_programBlur[0] = BGFX_INVALID_HANDLE;
		m_programBlur[1] = BGFX_INVALID_HANDLE;
		m_blurFB[0] = BGFX_INVALID_HANDLE;
		m_blurFB[1] = BGFX_INVALID_HANDLE;
		
		s_texColor = BGFX_INVALID_HANDLE; // Remember - bgfx::uniformHandles are reference counted by bgfx!
		u_blurParameters = BGFX_INVALID_HANDLE;
		u_screenSize = BGFX_INVALID_HANDLE;
		
		inited = false;
		viewId = 0;
		}
}
namespace bgfxh
{
  void guassianBlurEffect::setSize (uint32_t const _blurWidth, uint32_t const _blurHeight)
                                                                             {
		blurWidth = _blurWidth;
		blurHeight = _blurHeight; 
		}
}
namespace bgfxh
{
  void guassianBlurEffect::init ()
                     {
		m_blurFB[0] = bgfx::createFrameBuffer(blurWidth, blurHeight, framebufferTexFormat, BGFXH_RT_UV_CLAMP); // Bloom Tick
		m_blurFB[1] = bgfx::createFrameBuffer(blurWidth, blurHeight, framebufferTexFormat, BGFXH_RT_UV_CLAMP); // Bloom Tock
		bgfx::setName(m_blurFB[0], "Guassian Blur Tick");
		bgfx::setName(m_blurFB[1], "Guassian Blur Tock");
		s_texColor  = bgfx::createUniform("s_texColor",  bgfx::UniformType::Sampler);
		u_screenSize  = bgfx::createUniform("u_screenSize",  bgfx::UniformType::Vec4);
		
		// Auto pick a suitable sigma
		if (sigma < 1e-6) sigma = bgfxh::getGuassianSigmaFromKernalSize(kernalSize);
		u_blurParameters = bgfx::createUniform("u_blurParameters", bgfx::UniformType::Vec4, MAX_SAMPLES);
		
		BGFXH_ASSERT((int(kernalSize)/2+1-2 <= MAX_SAMPLES), "bgfxh::guassianBlurEffect: kernal size is too large! You'll have to change MAX_SAMPLES in bgfxh/effects/guassianBlur.h AND the size of u_blurParameters[] in bgfxh/shaders/guassian_blur/src/fs_guassian_blur.sc to match. MAX_SAMPLES = kernalSize/2-1");
		
		#ifdef BGFXH_EMBED_EFFECT_SHADERS
			{
			#include "../shaders/bloom/c/vs_guassian_blur_hz.bin.h"
			#include "../shaders/bloom/c/fs_guassian_blur_hz.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_guassian_blur_hz_bin),
				BGFXH_EMBEDDED_SHADER(fs_guassian_blur_hz_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programBlur[0] = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_guassian_blur_hz_bin")
													, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_guassian_blur_hz_bin")
													, true
													);
			}
			{
			#include "../shaders/bloom/c/vs_guassian_blur_vt.bin.h"
			#include "../shaders/bloom/c/fs_guassian_blur_vt.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_guassian_blur_vt_bin),
				BGFXH_EMBEDDED_SHADER(fs_guassian_blur_vt_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programBlur[1] = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_guassian_blur_vt_bin")
													, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_guassian_blur_vt_bin")
													, true
													);
			}
		#else
			m_programBlur[0] = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_guassian_blur_hz.bin", bgfxh::shaderSearchPath + "fs_guassian_blur_hz.bin");
			m_programBlur[1] = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_guassian_blur_vt.bin", bgfxh::shaderSearchPath + "fs_guassian_blur_vt.bin");
		#endif
			
		BGFXH_ASSERT(bgfx::isValid(m_programBlur[0]), "failed to load shader bgfxh::guassianBlurEffect::m_programBlur[0]! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		BGFXH_ASSERT(bgfx::isValid(m_programBlur[1]), "failed to load shader bgfxh::guassianBlurEffect::m_programBlur[1]! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		
		//fmt::println ("init! {} {} {} ", bgfx::isValid(m_bloomExtractProgram), bgfx::isValid(m_programBlur[0]), bgfx::isValid(m_programBlur[1]));
		//abort ();
		inited = true;
		}
}
namespace bgfxh
{
  void guassianBlurEffect::deInit ()
                       {
		// Frees resources if occupied. bgfxh::destroyhandle will null check
		bgfxh::destroyHandle (m_blurFB[0]);
		bgfxh::destroyHandle (m_blurFB[1]);
		bgfxh::destroyHandle (s_texColor);
		bgfxh::destroyHandle (u_blurParameters);
		
		bgfxh::destroyHandle (m_programBlur[0]);
		bgfxh::destroyHandle (m_programBlur[1]);
		inited = false;
		}
}
namespace bgfxh
{
  void guassianBlurEffect::submit_common (bgfx::TextureHandle const & colourBufferIn)
                                                                        {
		for (uint32_t i = 0; i < nBlurPasses; ++i) {
			bgfxh::initView2D (viewId+0+i*2, "Guassian Blur Horz", blurWidth, blurHeight, m_blurFB[0]);
			bgfxh::initView2D (viewId+1+i*2, "Guassian Blur Vert", blurWidth, blurHeight, m_blurFB[1]);
			}
		
		// Calcualte weights & setup uniforms
		double weights[kernalSize/2+1];
		double offsets[kernalSize/2+1];
		int nSamples = kernalSize/2+1;
		bgfxh::calcGuassianBlurWeights(kernalSize, sigma, weights, offsets);
		
		float blurParams[MAX_SAMPLES][4];
		blurParams[0][0] = weights[1];
		blurParams[0][1] = offsets[1];
		blurParams[0][2] = weights[0];
		blurParams[0][3] = float(nSamples - 0.01);
		uint16_t num = 1;
		for (int i = 1; i < nSamples-1; ++i) {
			blurParams[i][0] = weights[i+1];
			blurParams[i][1] = offsets[i+1];
			blurParams[i][2] = 0.f;
			blurParams[i][3] = 0.f;
			++num;
			}
		bgfx::setUniform(u_blurParameters, blurParams, num);
		
		float screenSize[4] = { float(blurWidth), float(blurHeight), float(bgfxh::screenWidth), float(bgfxh::screenHeight) };
		bgfx::setUniform(u_screenSize, screenSize);
		
		// Blur passes
		for (unsigned int i = 0; i < nBlurPasses; ++i) {
			if (i == 0)
				bgfx::setTexture(bgfxh::SAMPLER_COLOR , s_texColor, colourBufferIn );
			else
				bgfx::setTexture(bgfxh::SAMPLER_COLOR , s_texColor, bgfx::getTexture(m_blurFB[1]) );
			bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
			bgfxh::fullscreenQuad(blurWidth, blurHeight);
			bgfx::submit(viewId + 0 + i*2, m_programBlur[0]);
			
			bgfx::setTexture(bgfxh::SAMPLER_COLOR , s_texColor, bgfx::getTexture(m_blurFB[0]) );
			bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
			bgfxh::fullscreenQuad(blurWidth, blurHeight);
			bgfx::submit(viewId + 1 + i*2, m_programBlur[1]);
			}
		}
}
namespace bgfxh
{
  void guassianBlurEffect::submit (bgfx::TextureHandle const & colourBufferIn)
                                                                 {
		BGFXH_ASSERT(inited, "using a bgfxh::guassianBlurEffect without calling init()!");
		
		// Bloom without lum
		submit_common (colourBufferIn);
		}
}
#undef LZZ_INLINE
#endif //BGFXH_DOUBLE_GUARD_effects_guassianBlur
#endif //BGFXH_IMPL
