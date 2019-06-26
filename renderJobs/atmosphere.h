// atmosphere.hh
//

#ifndef LZZ_atmosphere_hh
#define LZZ_atmosphere_hh
// Non functioning WIP that should be used by noone
 
///////////////////////////////////////////////////////////////////////
// Atmosphere RenderJob
//
// Renders a spherical atmosphere. Can be used when rendering from the ground or from space
// Vertex OR fragment shader based. Set "mAtmosphere::doInFragShader = true" to enable fragment shader
// Contains a utility function (bgfxh::generateIsoSphere) to create a sky sphere, a sky dome (half iso-sphere),
// or a section of a sky sphere (with the minHeight argument)
//
// If you want to shade terrain, use the atmosphereGround() function in shaders/atmosphere/atmospheric_functions.shh
// 
// The sky sphere is an isosphere
// The sky dome is also an isosphere, but only triangles containing verts.y >= 0.f are subdivided.
// you can use the minHeight parameter to make sure that only verts.y > minHeight are subdivided
//
//
// How to use:
// 0. Include! Use #include <bgfxh/bgfxh.h>, #include <bgfxh/renderJobs/atmosphere.h> in a relevent file. Be sure to use #define BGFXH_IMPL *once* to generate an implementation somewhere!
// 1. Create an instance of the atmosphereRenderJob object ( bgfxh::atmosphereRenderJob mAtmosphereRenderJob; )
// 2. Set the user parameters to your liking.
// 3. Call mAtmosphereRenderJob.init() - this will generate framebuffers and uniforms and load the shaders
// 4. In your rendering loop submit geometry to the filter for each level
// 
// To create a sky sphere:
//	bgfxh::simpleMesh skyMesh;
//	bgfxh::generateIsoSphere(skyMesh, 4, useMinHeight = (false), minHeight = (0.f))
//	bgfxh::generateIsoSphere(skyMesh, 4) // Sphere with 4 subdivisions
//	bgfxh::generateIsoSphere(skyMesh, 4, true) // Sphere with 4 subdivisions, only y >= 0 verts are subdivided
//	bgfxh::generateIsoSphere(skyMesh, 4, true, 0.8) // Sphere with 4 subdivisions, only y >= 0.8 verts are subdivided
//
// To draw:
//	skyMesh.bind();
//	mAtmosphereRenderJob.setTransformMatrix (bgfxModelMtx, worldRadius, planetToSunDirection);
//	bgfx::setState (BGFX_WRITE_RGB | BGFX_WRITE_A);
//	mAtmosphereRenderJob.submit();
//
// Polygon Counts:
//	IsoSpheres: (useMinHeight = fasle)
//	SubDivisions: 0, nVerts: 12, nIndicies: 60, nTriangles: 20
//	SubDivisions: 1, nVerts: 42, nIndicies: 240, nTriangles: 80
//	SubDivisions: 2, nVerts: 162, nIndicies: 960, nTriangles: 320
//	SubDivisions: 3, nVerts: 642, nIndicies: 3840, nTriangles: 1280
//	SubDivisions: 4, nVerts: 2562, nIndicies: 15360, nTriangles: 5120
//	SubDivisions: 5, nVerts: 10242, nIndicies: 61440, nTriangles: 20480
//	SubDivisions: 6, nVerts: 40962, nIndicies: 245760, nTriangles: 81920
//	SubDivisions: 7, nVerts: 65730 !! Error -> vertex count is > 65355 and algo breaks
// Semi-IsoSpheres (useMinHeight = true, minHeight = 0.f)
//	SubDivisions: 0, nVerts: 12, nIndicies: 60, nTriangles: 20
//	SubDivisions: 1, nVerts: 41, nIndicies: 222, nTriangles: 74
//	SubDivisions: 2, nVerts: 133, nIndicies: 744, nTriangles: 248
//	SubDivisions: 3, nVerts: 441, nIndicies: 2526, nTriangles: 842
//	SubDivisions: 4, nVerts: 1541, nIndicies: 8988, nTriangles: 2996
//	SubDivisions: 5, nVerts: 5665, nIndicies: 33450, nTriangles: 11150
//	SubDivisions: 6, nVerts: 21597, nIndicies: 128472, nTriangles: 42824
//	SubDivisions: 7, nVerts: 84185 !! Error -> vertex count is > 65355 and algo breaks
//
//
// VIEWS: This renderJob will consume 0 views, but you need at least 1 view for it (you can use multiple atmospheres in 1 view)
//
///////////////////////////////////////////////////////////////////////

#include "../mesh.h"
#define LZZ_INLINE inline
namespace bgfxh
{
  void generateIsoSphere (bgfxh::simpleMesh & sm, unsigned int const nSubdivisions, bool useMinHeight = false, float minHeight = 0.f);
}
namespace bgfxh
{
  class atmosphericRenderJob : public renderJob
  {
  public:
    bgfx::UniformHandle u_sunDirection;
    bgfx::UniformHandle u_worldPosAndSize;
    bgfx::UniformHandle u_atmosphericParams;
    bgfx::ProgramHandle m_programAtmosphere;
    bool inited;
    bgfx::ViewId viewId;
    bool doInFragShader;
    atmosphericRenderJob ();
    ~ atmosphericRenderJob ();
    bgfx::FrameBufferHandle getOutputFrameBuffer () const;
    bgfx::TextureHandle getOutputTexture () const;
    int getViewIncrement () const;
    void initToZero ();
    void init ();
    void deInit ();
    void setTransforms (float const * modelMtx, float const planetRadius, bx::Vec3 const & sunPosition, float const & sunIntensity = 10.f, float const & g = -0.87, bx::Vec3 const & tintColor = bx::Vec3(1.f, 1.f, 1.f), bx::Vec3 const & rayleighTint = bx::Vec3(1.f, 1.f, 1.f));
    void submit ();
  };
}
namespace bgfxh
{
  LZZ_INLINE void atmosphericRenderJob::submit ()
                              {
		bgfx::submit (viewId, m_programAtmosphere);
		}
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
// atmosphere.cpp
//

#include "../bgfxh_embedded_shader.h"
#include <vector>
#include <unordered_map>
#define LZZ_INLINE inline
namespace bgfxh
{
  void generateIsoSphere (bgfxh::simpleMesh & sm, unsigned int const nSubdivisions, bool useMinHeight, float minHeight)
                                                                                                                                    {
	// Adapted from:
	// http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
	// https://schneide.blog/2016/07/15/generating-an-icosphere-in-c/
	const float gr = (1.0 + sqrt(5.0)) / 2.0;
	const float gri = 1.0/gr;
	
	std::unordered_map<uint32_t,uint16_t> dictionary;
	
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
		vector<meshFace> newFaces;
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
	
	// Get indicies from faces
	const uint32_t smFacesSz = sm.faces.size();
	sm.indicies.reserve(smFacesSz*3);
	for (uint32_t i = 0; i < smFacesSz; ++i) {
		const meshFace & tri = sm.faces[i];
		sm.indicies.push_back(tri.a);
		sm.indicies.push_back(tri.b);
		sm.indicies.push_back(tri.c);
		}
	}
}
namespace bgfxh
{
  atmosphericRenderJob::atmosphericRenderJob ()
                                { initToZero(); }
}
namespace bgfxh
{
  atmosphericRenderJob::~ atmosphericRenderJob ()
                                 { deInit(); }
}
namespace bgfxh
{
  bgfx::FrameBufferHandle atmosphericRenderJob::getOutputFrameBuffer () const
                                                              { return BGFX_INVALID_HANDLE; }
}
namespace bgfxh
{
  bgfx::TextureHandle atmosphericRenderJob::getOutputTexture () const
                                                      { return BGFX_INVALID_HANDLE; }
}
namespace bgfxh
{
  int atmosphericRenderJob::getViewIncrement () const
                                      { return 0; }
}
namespace bgfxh
{
  void atmosphericRenderJob::initToZero ()
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
  void atmosphericRenderJob::init ()
                     {
		u_sunDirection = bgfx::createUniform("u_sunDirection", bgfx::UniformType::Vec4); 
		u_worldPosAndSize = bgfx::createUniform("u_worldPosAndSize", bgfx::UniformType::Vec4);
		u_atmosphericParams = bgfx::createUniform("u_atmosphericParams", bgfx::UniformType::Vec4, 2);
		
		#ifdef BGFXH_EMBED_RENDER_JOB_SHADERS
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
		
		BGFXH_CHECK(bgfx::isValid(m_programAtmosphere), "failed to load shader bgfxh::atmosphericRenderJob::m_programAtmosphere! Check your bgfxh::shaderSearchPath setting, path, and that the shader type matches the renderer type!");
		inited = true;
		}
}
namespace bgfxh
{
  void atmosphericRenderJob::deInit ()
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
  void atmosphericRenderJob::setTransforms (float const * modelMtx, float const planetRadius, bx::Vec3 const & sunPosition, float const & sunIntensity, float const & g, bx::Vec3 const & tintColor, bx::Vec3 const & rayleighTint)
                                                                                                                                                                                                                                                                                       {
		bx::Vec3 planetPosition (modelMtx[12], modelMtx[13],modelMtx[14]);
		bx::Vec3 sunDirection = bx::normalize(bx::sub(sunPosition, planetPosition));
		
		float fa_sunDirection[4] = { sunDirection.x, sunDirection.y, sunDirection.z, 0.f };
		float fa_worldPosAndSize[4] = { planetPosition.x, planetPosition.y, planetPosition.z, planetRadius };
		float fa_atmosphericParams[8] = { tintColor.x, tintColor.y, tintColor.z, sunIntensity,
										 rayleighTint.x, rayleighTint.y, rayleighTint.z, g };
		bgfx::setUniform(u_sunDirection, fa_sunDirection);
		bgfx::setUniform(u_worldPosAndSize, fa_worldPosAndSize);
		bgfx::setUniform(u_atmosphericParams, fa_atmosphericParams, 2);
		bgfx::setTransform(modelMtx);
		}
}
#undef LZZ_INLINE
#endif //BGFXH_IMPL
