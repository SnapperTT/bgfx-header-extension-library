// cascadingShadowMap.hh
//

#ifndef LZZ_cascadingShadowMap_hh
#define LZZ_cascadingShadowMap_hh
///////////////////////////////////////////////////////////////////////
// Cascading Shadow Map Filter
// Creates shadow maps. For rending you scence you still have to implement shadowing in shaders yourself
// 
// How to use:
// 0. Include! Use #include <bgfxh/bgfxh.h>, #include <bgfxh/cascadingShadowMap.h> in a relevent file. Be sure to use #define BGFXH_IMPL *once* to generate an implementation somewhere!
// 1. Create an instance of the cascadingShadowFilter object ( bgfxh::cascadingShadowFilter cShadowFilter; )
// 2. Set the user parameters to your liking. depthGates is important to set!
// 3. Call cascadingShadowFilter.init() - this will generate framebuffers and uniforms and load the shaders
// 4. In your rendering loop submit geometry to the filter for each level
// 5. Use the output as a sampler with cShadowFilter.getOutputTexture(csmLevel)
// 
// To use a a non-cascading shadow map
// 1. Set nShdaowMaps to 1.
// 2. Set depthGates[0] to your far clip plane distance
//
// To use Variance Shadow Mapping
// 1. Set useVsm to true.
//
// VIEWS: This filter will consume nShadowLevels views
//
///////////////////////////////////////////////////////////////////////
//	Example usuage:
//	int main ( ... ) {
//	
//	initWindowAndBgfx();
//	
//	bgfxh::cascadingShadowFilter cShadowFilter;
//	cShadowFilter.viewId = ... ;
//	cShadowFilter.useVsm = ... ;
//	cShadowFilter.nShadowLevels = ... ;
//	cShadowFilter.init();
//
//	while (true) {
//		float[16] viewMtx = ... ;
//		float[16] projMtx = ... ;
//		bx::Vec3 lightDirection ( ... );
//		cShadowFilter.setupViews (viewMtx, projMtx, lightDirection, HORZ_FOV, VERT_FOV);
//		
//		// Submitting to shadow maps
//		for (uint32_t csmLevel = 0; csmLevel < cShadowFiler.nShadowLevels; ++csmLevel) {
//			for (geometry in scene) {
//				if (!cShadowFiler.isObjectInShadowVolume (geometry.modelPos, geometry.boundingRadius, csmLevel))
//					continue;
//				bgfx::setTransform(geometry.modelMtx);
//				bgfx::bind(geometry.vertxBufferHandle);
//				bgfx::setState(cShadowFilter.submitState | BGFX_STATE_CULL_CW);
//				cShadowFilter.submit(csmLevel);
//				}
//			}
//
//		// Submitting geometry
//		initMainPassView ( ... );
//		bgfxh::frustum m_frustum(view, proj);
//		bool isFirst = true;
//		for (geometry in scene) {
//			if (!bgfxh::frustrumCheck(m_frustum, geometry.modelPos, geometry.boundingRadius)) continue;
//
//			if (isFirst) {
//				cShadowFiler.bindSamplers ();
//				isFirst = false;
//				}
//			cShadowFiler.setLightMVP (geometry.modelMtx); // Sets the u_lightMtx[] uniforms for shaders
//			bgfx::setTransform (geometry.modelMtx);
//
//			bgfx::setTexture (..., ...); // Diffuse, normal, etc
//			bgfx::setState (...);
//			bgfx::submit (forwardRenderViewId, forwardRenderingProgram);
//			}
//
//		// Viewing shadow maps
//		bgfxh::initView2D (VIEW_DEBUG_PASS, "output pass", windowWidth, windowHeight, BGFX_INVALID_HANDLE, false, false);
//		for (uint32_t csmLevel = 0; csmLevel < cShadowFiler.nShadowLevels; ++csmLevel)
//			bgfxh::debugDrawFramebufferMono (VIEW_DEBUG_PASS, cShadowFiler.getOutputFrameBuffer(i), 20 + 120*csmLevel, 20, 120, 120, windowWidth, windowHeight);
//		
//		bgfx::frame();
//		}
//

// TODO: Use bounding spheres to calculate bounding volumes: https://lxjk.github.io/2017/04/15/Calculate-Minimal-Bounding-Sphere-of-Frustum.html
// TODO: Investigate automatic instancing of submission objects and rendering to a single target


#ifndef BGFXH_MAX_SHADOW_LEVELS
	#define BGFXH_MAX_SHADOW_LEVELS 4
#endif
#define LZZ_INLINE inline
namespace bgfxh
{
  class cascadingShadowMapEffect : public renderJob
  {
  public:
    bgfx::FrameBufferHandle (m_shadowMapFB) [BGFXH_MAX_SHADOW_LEVELS];
    bgfx::UniformHandle (u_lightMtx) [BGFXH_MAX_SHADOW_LEVELS];
    bgfx::UniformHandle (s_shadowMap) [BGFXH_MAX_SHADOW_LEVELS];
    float ((shadowLightView) [BGFXH_MAX_SHADOW_LEVELS]) [16];
    float ((shadowLightProj) [BGFXH_MAX_SHADOW_LEVELS]) [16];
    float ((shadowLightViewProj) [BGFXH_MAX_SHADOW_LEVELS]) [16];
    bx::Vec3 (shadowAabbMin) [BGFXH_MAX_SHADOW_LEVELS];
    bx::Vec3 (shadowAabbMax) [BGFXH_MAX_SHADOW_LEVELS];
    bgfx::ProgramHandle m_programDepthWrite;
    bool inited;
    float (depthGates) [BGFXH_MAX_SHADOW_LEVELS];
    float zMargin;
    bgfx::ViewId viewId;
    uint32_t nShadowLevels;
    uint32_t shadowMapSz;
    uint64_t submitState;
    bool shadowUseForwardZ;
    bool useVsm;
    bgfx::TextureFormat::Enum depthFormat;
    bgfx::TextureFormat::Enum vsmFormat;
    cascadingShadowMapEffect ();
    ~ cascadingShadowMapEffect ();
    bgfx::FrameBufferHandle getOutputFrameBuffer (unsigned int const csmLevel) const;
    bgfx::TextureHandle getOutputTexture (unsigned int const csmLevel) const;
    bgfx::FrameBufferHandle getOutputFrameBuffer () const;
    bgfx::TextureHandle getOutputTexture () const;
    int getViewIncrement () const;
    void initToZero ();
    void init ();
    void deInit ();
    void setupViews (float * viewMtx, float * projMtx, bx::Vec3 const & lightDirection, float const FOV_H_DEG, float const FOV_V_DEG);
    bool isObjectInShadowVolume (bx::Vec3 const & _pos, float const radius, unsigned int const csmLevel);
    float internal_sqDistPointAabb (bx::Vec3 const & point, bx::Vec3 const & aabbMin, bx::Vec3 const & aabbMax);
    void submit (uint32_t const level);
    void bindSamplers (unsigned int shadowSampler0);
    void setLightMVP (float const * modelMtx);
  };
}
namespace bgfxh
{
  LZZ_INLINE void cascadingShadowMapEffect::submit (uint32_t const level)
                                                  {
		bgfx::submit (viewId + level, m_programDepthWrite);
		}
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
#ifndef BGFXH_DOUBLE_GUARD_effects_cascadingShadowMap
#define BGFXH_DOUBLE_GUARD_effects_cascadingShadowMap
// cascadingShadowMap.cpp
//

#include <stdio.h> //printf
#define LZZ_INLINE inline
namespace bgfxh
{
  cascadingShadowMapEffect::cascadingShadowMapEffect ()
                                    { initToZero(); }
}
namespace bgfxh
{
  cascadingShadowMapEffect::~ cascadingShadowMapEffect ()
                                     { deInit(); }
}
namespace bgfxh
{
  bgfx::FrameBufferHandle cascadingShadowMapEffect::getOutputFrameBuffer (unsigned int const csmLevel) const
                                                                                         { return m_shadowMapFB[csmLevel]; }
}
namespace bgfxh
{
  bgfx::TextureHandle cascadingShadowMapEffect::getOutputTexture (unsigned int const csmLevel) const
                                                                                 { ///Returns the output framebuffer as a texture handle. Use this to use the output of a filter as a sampler input to another
		bgfx::FrameBufferHandle ofb = getOutputFrameBuffer(csmLevel);
		if (!bgfx::isValid(ofb)) return BGFX_INVALID_HANDLE;
		return bgfx::getTexture(ofb, 0);
		}
}
namespace bgfxh
{
  bgfx::FrameBufferHandle cascadingShadowMapEffect::getOutputFrameBuffer () const
                                                              { return getOutputFrameBuffer(0); }
}
namespace bgfxh
{
  bgfx::TextureHandle cascadingShadowMapEffect::getOutputTexture () const
                                                      { return getOutputTexture(0); }
}
namespace bgfxh
{
  int cascadingShadowMapEffect::getViewIncrement () const
                                      { return nShadowLevels; }
}
namespace bgfxh
{
  void cascadingShadowMapEffect::initToZero ()
                           {
		for (unsigned int i = 0; i < BGFXH_MAX_SHADOW_LEVELS; ++i) {
			m_shadowMapFB[i] = BGFX_INVALID_HANDLE;
			s_shadowMap[i] = BGFX_INVALID_HANDLE;
			u_lightMtx[i] = BGFX_INVALID_HANDLE;
			depthGates[i] = i * 9999.f / BGFXH_MAX_SHADOW_LEVELS;
			shadowAabbMin[i] = bx::Vec3(0.f, 0.f, 0.f);
			shadowAabbMax[i] = bx::Vec3(0.f, 0.f, 0.f);
			bx::mtxIdentity(shadowLightView[i]);
			bx::mtxIdentity(shadowLightProj[i]);
			bx::mtxIdentity(shadowLightViewProj[i]);
			}
		if (BGFXH_MAX_SHADOW_LEVELS > 0) depthGates[0] = 20.0f;
		if (BGFXH_MAX_SHADOW_LEVELS > 1) depthGates[1] = 100.0f;
		if (BGFXH_MAX_SHADOW_LEVELS > 2) depthGates[2] = 400.0f;
		if (BGFXH_MAX_SHADOW_LEVELS > 3) depthGates[3] = 1000.0f;
		m_programDepthWrite = BGFX_INVALID_HANDLE;
		
		viewId = 0;
		zMargin = 50;
		nShadowLevels = BGFXH_MAX_SHADOW_LEVELS;
		shadowMapSz = 512; 
		submitState = 0;
		shadowUseForwardZ = true;
		useVsm = false;
		depthFormat = bgfx::TextureFormat::D32F;
		vsmFormat   = bgfx::TextureFormat::RG32F;
		inited = false;
		}
}
namespace bgfxh
{
  void cascadingShadowMapEffect::init ()
                     {
		const uint64_t shadowTexFlags = BGFX_TEXTURE_RT
				 | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP;
		for (unsigned int i = 0; i < nShadowLevels; ++i) {
			if (useVsm) {
				// Variance shadow maps write depth to the red channel and depth squared to the green channel
				bgfx::TextureHandle shadowProxTex[2];
				shadowProxTex[0] = bgfx::createTexture2D(shadowMapSz, shadowMapSz, false, 1, vsmFormat, shadowTexFlags);
				shadowProxTex[1] = bgfx::createTexture2D(shadowMapSz, shadowMapSz, false, 1, depthFormat, shadowTexFlags); // Need for depth testing!
				m_shadowMapFB[i] = bgfx::createFrameBuffer(2, shadowProxTex, true);
				}
			else {
				bgfx::TextureHandle shadowProxTex[1];
				shadowProxTex[0] = bgfx::createTexture2D(shadowMapSz, shadowMapSz, false, 1, depthFormat, shadowTexFlags);
				m_shadowMapFB[i] = bgfx::createFrameBuffer(1, shadowProxTex, true);
				}
			char buf[32];
			sprintf(buf, "m_shadowMapFB%i", i);
			bgfx::setName(m_shadowMapFB[i], buf);
			sprintf(buf, "s_shadowMap%i", i);
			s_shadowMap[i] = bgfx::createUniform(buf,  bgfx::UniformType::Sampler); 
			sprintf(buf, "u_lightMtx%i", i);
			u_lightMtx[i] = bgfx::createUniform(buf,  bgfx::UniformType::Mat4); 
			}
		
		#ifdef BGFXH_EMBED_EFFECT_SHADERS
			if (useVsm) {
			#include "../shaders/cascading_shadow_map/c/vs_cascading_shadow_map_vsm.bin.h"
			#include "../shaders/cascading_shadow_map/c/fs_cascading_shadow_map_vsm.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_cascading_shadow_map_vsm_bin),
				BGFXH_EMBEDDED_SHADER(fs_cascading_shadow_map_vsm_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programDepthWrite = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_cascading_shadow_map_vsm_bin")
													, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_cascading_shadow_map_vsm_bin")
													, true
													);
			}
			else {
			#include "../shaders/cascading_shadow_map/c/vs_cascading_shadow_map.bin.h"
			#include "../shaders/cascading_shadow_map/c/fs_cascading_shadow_map.bin.h"

			static const bgfx::EmbeddedShader s_embeddedShaders[] = {
				BGFXH_EMBEDDED_SHADER(vs_cascading_shadow_map_bin),
				BGFXH_EMBEDDED_SHADER(fs_cascading_shadow_map_bin),
				
				BGFX_EMBEDDED_SHADER_END()
				};
			
			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_programDepthWrite = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_cascading_shadow_map_bin")
													, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_cascading_shadow_map_bin")
													, true
													);
			}
		#else
			if (useVsm)
				m_programDepthWrite = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_cascading_shadow_map_vsm.bin", bgfxh::shaderSearchPath + "fs_cascading_shadow_map_vsm.bin");
			else
				m_programDepthWrite = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_cascading_shadow_map.bin", bgfxh::shaderSearchPath + "fs_cascading_shadow_map.bin");
		#endif
		
		BGFXH_ASSERT(bgfx::isValid(m_programDepthWrite), "failed to load shader bgfxh::cascadingShadowMapEffect::m_programDepthWrite! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		inited = true;
		}
}
namespace bgfxh
{
  void cascadingShadowMapEffect::deInit ()
                       {
		for (unsigned int i = 0; i < BGFXH_MAX_SHADOW_LEVELS; ++i) {
			bgfxh::destroyHandle (m_shadowMapFB[i]);
			bgfxh::destroyHandle (u_lightMtx[i]);
			bgfxh::destroyHandle (s_shadowMap[i]);
			}
		bgfxh::destroyHandle (m_programDepthWrite);
		inited = false;
		}
}
namespace bgfxh
{
  void cascadingShadowMapEffect::setupViews (float * viewMtx, float * projMtx, bx::Vec3 const & lightDirection, float const FOV_H_DEG, float const FOV_V_DEG)
                                                                                                                                          {
		const bool shadowUseForwardZ = true;
		const uint64_t STATE_SHADOW_DEPTH_TEST = shadowUseForwardZ ? BGFX_STATE_DEPTH_TEST_LESS : BGFX_STATE_DEPTH_TEST_GREATER;
		const uint32_t shadowClearColour = shadowUseForwardZ ? 0xffffffff : 0x00000000;
		submitState = STATE_SHADOW_DEPTH_TEST | BGFX_STATE_WRITE_Z;
		if (useVsm) submitState |= BGFX_STATE_WRITE_R | BGFX_STATE_WRITE_G;
		const bgfx::Caps * caps = bgfx::getCaps();
		
		for (unsigned int i = 0; i < nShadowLevels; ++i) {
			// Set the view matrix
			bx::mtxLookAt(shadowLightView[i], lightDirection, bx::Vec3(0.f, 0.f, 0.f));
			
			// Set the projection matrix
			// This is done by slicing the frustum into several sub-frustum
			// starting at one depth position and ending at another
			// The projection matrix is then constructed as a box
			// that encompases the sub-frustum
			float z1 = i ? depthGates[i-1] : 0.f;
			float z2 = depthGates[i];
			float x1 = z1 * tan(bx::toRad(FOV_H_DEG)/2.0f);
			float x2 = z2 * tan(bx::toRad(FOV_H_DEG)/2.0f);
			float y1 = z1 * tan(bx::toRad(FOV_V_DEG)/2.0f);
			float y2 = z2 * tan(bx::toRad(FOV_V_DEG)/2.0f);
			
			bx::Vec3 coords[8];
			coords[0] = bx::Vec3( x1, y1,z1);
			coords[1] = bx::Vec3(-x1,-y1,z1);
			coords[2] = bx::Vec3( x2, y2,z2);
			coords[3] = bx::Vec3(-x2,-y2,z2);
			coords[4] = bx::Vec3( x1,-y1,z1);
			coords[5] = bx::Vec3(-x1, y1,z1);
			coords[6] = bx::Vec3( x2,-y2,z2);
			coords[7] = bx::Vec3(-x2, y2,z2);
			
			for (unsigned int j = 0; j < 8; ++j)
				coords[j] = bx::mul(coords[j], shadowLightView[i]);
			
			float minX = HUGE_VAL;
			float minY = HUGE_VAL;
			float minZ = HUGE_VAL;
			float maxX = -HUGE_VAL;
			float maxY = -HUGE_VAL;
			float maxZ = -HUGE_VAL;
			
			for (unsigned int j = 0; j < 8; ++j) {
				minX = min(minX, coords[j].x);
				minY = min(minY, coords[j].y);
				minZ = min(minZ, coords[j].z);
				maxX = max(maxX, coords[j].x);
				maxY = max(maxY, coords[j].y);
				maxZ = max(maxZ, coords[j].z);
				}
			
			const float safetyFactor = 1.25; //Padding so that objects don't get clipped
			float zSz = maxZ - minZ;
			float zAvg = (maxZ + minZ)/2;
			minZ = zAvg - zSz*safetyFactor/2.0 - zMargin;
			maxZ = zAvg + zSz*safetyFactor/2.0 + zMargin;
			
			shadowAabbMin[i] = bx::Vec3(minX, minY, minZ);
			shadowAabbMax[i] = bx::Vec3(maxX, maxY, maxZ);
			
			bx::mtxOrtho(shadowLightProj[i], minX, maxX, minY, maxY, minZ, maxZ, 0.0f, caps->homogeneousDepth);
			}
		
		// Always render all shadows			
		for (unsigned int i = 0; i < nShadowLevels; ++i) {
			bgfx::setViewName(viewId + i, "ShadowPass");
			bgfx::setViewRect(viewId + i, 0, 0, shadowMapSz, shadowMapSz);
			bgfx::setViewFrameBuffer(viewId + i, m_shadowMapFB[i]);
			bgfx::setViewClear(viewId + i, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, shadowClearColour, shadowUseForwardZ ? 1.0f : 0.0f, 0);
			bgfx::setViewTransform(viewId + i, shadowLightView[i], shadowLightProj[i]);
			}
		
		// Setup the shadow VP matrix
		const float sy = caps->originBottomLeft ? 0.5f : -0.5f;
		const float sz = caps->homogeneousDepth ? 0.5f :  1.0f;
		const float tz = caps->homogeneousDepth ? 0.5f :  0.0f;
		const float mtxCrop[16] =
		{
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f,   sy, 0.0f, 0.0f,
			0.0f, 0.0f, sz,   0.0f,
			0.5f, 0.5f, tz,   1.0f,
		};
		
		// Set shadow mapping transform uniforms
		float mtxTmp[16];
		for (unsigned int i = 0; i < nShadowLevels; ++i) {
			bx::mtxMul(mtxTmp,       		   shadowLightProj[i], mtxCrop);
			bx::mtxMul(shadowLightViewProj[i], shadowLightView[i], mtxTmp);
			bgfx::setUniform(u_lightMtx[i], shadowLightView[i]);
			}
		}
}
namespace bgfxh
{
  bool cascadingShadowMapEffect::isObjectInShadowVolume (bx::Vec3 const & _pos, float const radius, unsigned int const csmLevel)
                                                                                                             {
		/// Checks if an object at a position and radius 
		/// TODO: simd optimisation
		const bx::Vec3 pos = bx::mul(_pos, shadowLightView[csmLevel]); // Get the object's position in light-view space
		float d2 = internal_sqDistPointAabb (pos, shadowAabbMin[csmLevel], shadowAabbMax[csmLevel]);
		return d2 < (radius * radius);
		}
}
namespace bgfxh
{
  float cascadingShadowMapEffect::internal_sqDistPointAabb (bx::Vec3 const & point, bx::Vec3 const & aabbMin, bx::Vec3 const & aabbMax)
                                                                                                                    {
		/// Returns the distance squared to an aabb
		float maxDist2 = 0.0;
		{
			const float & v = point.x;
			if (v < aabbMin.x) maxDist2 += (aabbMin.x - v) * (aabbMin.x - v);
			if (v > aabbMax.x) maxDist2 += (aabbMax.x - v) * (aabbMax.x - v);
		}{
			const float & v = point.y;
			if (v < aabbMin.y) maxDist2 += (aabbMin.y - v) * (aabbMin.y - v);
			if (v > aabbMax.y) maxDist2 += (aabbMax.y - v) * (aabbMax.y - v);
		}{
			const float & v = point.z;
			if (v < aabbMin.z) maxDist2 += (aabbMin.z - v) * (aabbMin.z - v);
			if (v > aabbMax.z) maxDist2 += (aabbMax.z - v) * (aabbMax.z - v);
		}
		return maxDist2;
		}
}
namespace bgfxh
{
  void cascadingShadowMapEffect::bindSamplers (unsigned int shadowSampler0)
                                                        {
		for (unsigned int csmLevel = 0; csmLevel < nShadowLevels; ++csmLevel)
			bgfx::setTexture (shadowSampler0 + csmLevel, s_shadowMap[csmLevel], getOutputTexture(csmLevel));
		}
}
namespace bgfxh
{
  void cascadingShadowMapEffect::setLightMVP (float const * modelMtx)
                                                  {
		for (unsigned int csmLevel = 0; csmLevel < nShadowLevels; ++csmLevel) {
			float mvp_shadow[16];
			bx::mtxMul(mvp_shadow, modelMtx, shadowLightViewProj[csmLevel]);
			bgfx::setUniform (u_lightMtx[csmLevel], mvp_shadow);
			}
		}
}
#undef LZZ_INLINE
#endif //BGFXH_DOUBLE_GUARD_effects_cascadingShadowMap
#endif //BGFXH_IMPL
