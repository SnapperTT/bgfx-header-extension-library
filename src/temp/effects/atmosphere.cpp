// atmosphere.cpp
//

#include "atmosphere.hh"
#include "../bgfxh_embedded_shader.h"
#include <unordered_map>
#define LZZ_INLINE inline
namespace bgfxh
{
  void generateIsoSphere (bgfxh::simpleMesh & sm, unsigned int const nSubdivisions, bool useMinHeight, float minHeight)
                                                                                                                                    {
	// Adapted from:
	// http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
	// https://schneide.blog/2016/07/15/generating-an-icosphere-in-c/
	//
	// Performance notes: This is very slow for nSubdivisions > 3. You should save pregenerated isospheres and just load them directly 
	// This could be sped up by only subdividing one face, then using symmetery to copy the results
	// Can also be sped up by using a thread pool on subdivisions, but this is probably overkill
	//
	const float gr = (1.0 + sqrt(5.0)) / 2.0;
	const float gri = 1.0/gr;
	
	#ifdef TSL_ROBIN_MAP_H
		// use a better-performing robin map if <tsl/robin_map.h> has been included
		tsl::robin_map<uint32_t,uint16_t> dictionary;
	#else
		std::unordered_map<uint32_t,uint16_t> dictionary;
	#endif
	
	auto getGenMiddlePoint = [&](const uint16_t p1, const uint16_t p2) -> uint16_t {
		/// Returns or inserts a index
		// first check if we have it already
		const bool firstIsSmaller = p1 < p2;
		const uint32_t smallerIndex = firstIsSmaller ? p1 : p2;
		const uint32_t greaterIndex = firstIsSmaller ? p2 : p1;
		const uint32_t key = (smallerIndex << 16) | greaterIndex;
		const uint16_t val = sm.verts.size();

		auto inserted = dictionary.insert({key, val});
		if (inserted.second) {
			const bx::Vec3 & edge0 = sm.verts[p1];
			const bx::Vec3 & edge1 = sm.verts[p2];
			
			if (useMinHeight) {
				if (edge0.y < minHeight && edge1.y < minHeight) {
					bx::Vec3 point = bx::lerp(edge0, edge1, 0.5f); // Average so that there are no gaps
					sm.verts.push_back(point);
					return sm.verts.size()-1; 
					}
				}
			bx::Vec3 point = bx::normalize(bx::add(edge0,edge1)); // Project onto sphere
			sm.verts.push_back(point);
			return sm.verts.size()-1; 
			}

		return inserted.first->second;
		};
	
	// Generate initial isohedron
	sm.verts.push_back(bx::normalize(bx::Vec3(-gri,  1,  0)));
	sm.verts.push_back(bx::normalize(bx::Vec3( gri,  1,  0)));
	sm.verts.push_back(bx::normalize(bx::Vec3(-gri, -1,  0)));
	sm.verts.push_back(bx::normalize(bx::Vec3( gri, -1,  0)));

	sm.verts.push_back(bx::normalize(bx::Vec3( 0, -gri,  1)));
	sm.verts.push_back(bx::normalize(bx::Vec3( 0,  gri,  1)));
	sm.verts.push_back(bx::normalize(bx::Vec3( 0, -gri, -1)));
	sm.verts.push_back(bx::normalize(bx::Vec3( 0,  gri, -1)));

	sm.verts.push_back(bx::normalize(bx::Vec3( 1,  0, -gri)));
	sm.verts.push_back(bx::normalize(bx::Vec3( 1,  0,  gri)));
	sm.verts.push_back(bx::normalize(bx::Vec3(-1,  0, -gri)));
	sm.verts.push_back(bx::normalize(bx::Vec3(-1,  0,  gri)));
	
	// Faces
	sm.faces.push_back(meshFace(0, 11, 5));
	sm.faces.push_back(meshFace(0, 5, 1));
	sm.faces.push_back(meshFace(0, 1, 7));
	sm.faces.push_back(meshFace(0, 7, 10));
	sm.faces.push_back(meshFace(0, 10, 11));

	sm.faces.push_back(meshFace(1, 5, 9));
	sm.faces.push_back(meshFace(5, 11, 4));
	sm.faces.push_back(meshFace(11, 10, 2));
	sm.faces.push_back(meshFace(10, 7, 6));
	sm.faces.push_back(meshFace(7, 1, 8));

	sm.faces.push_back(meshFace(3, 9, 4));
	sm.faces.push_back(meshFace(3, 4, 2));
	sm.faces.push_back(meshFace(3, 2, 6));
	sm.faces.push_back(meshFace(3, 6, 8));
	sm.faces.push_back(meshFace(3, 8, 9));

	sm.faces.push_back(meshFace(4, 9, 5));
	sm.faces.push_back(meshFace(2, 4, 11));
	sm.faces.push_back(meshFace(6, 2, 10));
	sm.faces.push_back(meshFace(8, 6, 7));
	sm.faces.push_back(meshFace(9, 8, 1));
	
	// Subdivide!
	for (unsigned int ii = 0; ii < nSubdivisions; ii++) {
		const uint16_t smFacesSz = sm.faces.size();
		BGFXH_VECTOR<meshFace> newFaces;
		for (uint16_t i = 0; i < smFacesSz; ++i) {
			const meshFace & tri = sm.faces[i];
			
			if (useMinHeight) {
				// Don't subdivide any "underground" triangles
				const float & y1 = sm.verts[tri.a].y;
				const float & y2 = sm.verts[tri.b].y;
				const float & y3 = sm.verts[tri.c].y;
				if (y1 < minHeight && y2 < minHeight && y3 < minHeight) {
					newFaces.push_back(meshFace(tri.a, tri.b, tri.c));
					continue;
					}
				}
			
			uint16_t a = getGenMiddlePoint(tri.a, tri.b);
			uint16_t b = getGenMiddlePoint(tri.b, tri.c);
			uint16_t c = getGenMiddlePoint(tri.a, tri.c);
			newFaces.push_back(meshFace(tri.a, a, c));
			newFaces.push_back(meshFace(tri.b, b, a));
			newFaces.push_back(meshFace(tri.c, c, b));
			newFaces.push_back(meshFace(a, b, c));
			}
		sm.faces.swap(newFaces);
		}
	
	// Get indices from faces
	const uint32_t smFacesSz = sm.faces.size();
	sm.indices.reserve(smFacesSz*3);
	for (uint32_t i = 0; i < smFacesSz; ++i) {
		const meshFace & tri = sm.faces[i];
		sm.indices.push_back(tri.a);
		sm.indices.push_back(tri.b);
		sm.indices.push_back(tri.c);
		}
	}
}
namespace bgfxh
{
  atmosphericEffect::atmosphericEffect ()
                             { initToZero(); }
}
namespace bgfxh
{
  atmosphericEffect::~ atmosphericEffect ()
                              { deInit(); }
}
namespace bgfxh
{
  bgfx::FrameBufferHandle atmosphericEffect::getOutputFrameBuffer () const
                                                              { return BGFX_INVALID_HANDLE; }
}
namespace bgfxh
{
  bgfx::TextureHandle atmosphericEffect::getOutputTexture () const
                                                      { return BGFX_INVALID_HANDLE; }
}
namespace bgfxh
{
  int atmosphericEffect::getViewIncrement () const
                                      { return 0; }
}
namespace bgfxh
{
  void atmosphericEffect::initToZero ()
                           {
		u_sunDirection = BGFX_INVALID_HANDLE; 		// Sun vector in world. Normaised direction to it.
		u_worldPosAndSize = BGFX_INVALID_HANDLE; 	// The position and size of the world being rendered. (x,y,z) = position of the world in model space, w = world radius
		u_atmosphericParams = BGFX_INVALID_HANDLE;
		
		m_programAtmosphere = BGFX_INVALID_HANDLE;
		
		viewId = 0;
		doInFragShader = true;
		inited = false;
		}
}
namespace bgfxh
{
  void atmosphericEffect::init ()
                     {
		BGFXH_ASSERT(!inited, "double initialisation");
		
		u_sunDirection = bgfx::createUniform("u_sunDirection", bgfx::UniformType::Vec4); 
		u_worldPosAndSize = bgfx::createUniform("u_worldPosAndSize", bgfx::UniformType::Vec4);
		u_atmosphericParams = bgfx::createUniform("u_atmosphericParams", bgfx::UniformType::Vec4, 2);
		
		#ifdef BGFXH_EMBED_EFFECT_SHADERS
			if (doInFragShader) {
				#include "../shaders/atmosphere/c/vs_atmosphere.bin.h"
				#include "../shaders/atmosphere/c/fs_atmosphere.bin.h"

				static const bgfx::EmbeddedShader s_embeddedShaders[] = {
					BGFXH_EMBEDDED_SHADER(vs_atmosphere_bin),
					BGFXH_EMBEDDED_SHADER(fs_atmosphere_bin),
					
					BGFX_EMBEDDED_SHADER_END()
					};
				
				bgfx::RendererType::Enum type = bgfx::getRendererType();
				m_programAtmosphere = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_atmosphere_bin")
														, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_atmosphere_bin")
														, true
														);
				}
			else {
				#include "../shaders/atmosphere/c/vs_atmosphere_frag.bin.h"
				#include "../shaders/atmosphere/c/fs_atmosphere_frag.bin.h"

				static const bgfx::EmbeddedShader s_embeddedShaders[] = {
					BGFXH_EMBEDDED_SHADER(vs_atmosphere_frag_bin),
					BGFXH_EMBEDDED_SHADER(fs_atmosphere_frag_bin),
					
					BGFX_EMBEDDED_SHADER_END()
					};
				
				bgfx::RendererType::Enum type = bgfx::getRendererType();
				m_programAtmosphere = bgfx::createProgram(bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_atmosphere_frag_bin")
														, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_atmosphere_frag_bin")
														, true
														);
				}
		#else
			if (doInFragShader)
				m_programAtmosphere = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_atmosphere_frag.bin", bgfxh::shaderSearchPath + "fs_atmosphere_frag.bin");
			else
				m_programAtmosphere = bgfxh::loadProgram(bgfxh::shaderSearchPath + "vs_atmosphere.bin", bgfxh::shaderSearchPath + "fs_atmosphere.bin");
		#endif
		
		BGFXH_ASSERT(bgfx::isValid(m_programAtmosphere), "failed to load shader bgfxh::atmosphericEffect::m_programAtmosphere! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		inited = true;
		}
}
namespace bgfxh
{
  void atmosphericEffect::deInit ()
                       {			
		bgfxh::destroyHandle (u_sunDirection);
		bgfxh::destroyHandle (u_worldPosAndSize);
		bgfxh::destroyHandle (u_atmosphericParams);
			
		bgfxh::destroyHandle (m_programAtmosphere);
		inited = false;
		}
}
namespace bgfxh
{
  void atmosphericEffect::setTransforms (float const * modelMtx, float const planetRadius, bx::Vec3 const & sunPosition, float const & sunIntensity, float const & g, bx::Vec3 const & mieTint, bx::Vec3 const & rayleighTint)
                                                                                                                                                                                                                                                                                     {
		bx::Vec3 planetPosition (modelMtx[12], modelMtx[13],modelMtx[14]);
		bx::Vec3 sunDirection = bx::normalize(bx::sub(sunPosition, planetPosition));
		
		float fa_sunDirection[4] = { sunDirection.x, sunDirection.y, sunDirection.z, 0.f };
		float fa_worldPosAndSize[4] = { planetPosition.x, planetPosition.y, planetPosition.z, planetRadius };
		float fa_atmosphericParams[8] = { mieTint.x, mieTint.y, mieTint.z, sunIntensity,
										 rayleighTint.x, rayleighTint.y, rayleighTint.z, g };
		bgfx::setUniform(u_sunDirection, fa_sunDirection);
		bgfx::setUniform(u_worldPosAndSize, fa_worldPosAndSize);
		bgfx::setUniform(u_atmosphericParams, fa_atmosphericParams, 2);
		bgfx::setTransform(modelMtx);
		}
}
#undef LZZ_INLINE
