// mesh.hh
//

#ifndef LZZ_mesh_hh
#define LZZ_mesh_hh

#include <vector>
#define LZZ_INLINE inline
namespace bgfxh
{
  struct meshFace
  {
    uint16_t a;
    uint16_t b;
    uint16_t c;
    meshFace ();
    meshFace (uint16_t const _a, uint16_t const _b, uint16_t const _c);
  };
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE>
  struct mesh
  {
    vector <VERT_TYPE> verts;
    vector <uint16_t> indicies;
    vector <meshFace> faces;
    bgfx::VertexBufferHandle m_vbh;
    bgfx::IndexBufferHandle m_ibh;
    mesh ();
    ~ mesh ();
    static void internal_freeVerts_cb (void * _ptr, void * _userData);
    static void internal_freeIndicies_cb (void * _ptr, void * _userData);
    void upload (bool freeOnUploadComplete = true);
    void bind ();
    void destroy ();
  };
}
namespace bgfxh
{
  typedef mesh <bx::Vec3, PosVertex> simpleMesh;
}
namespace bgfxh
{
  LZZ_INLINE meshFace::meshFace ()
                                   {}
}
namespace bgfxh
{
  LZZ_INLINE meshFace::meshFace (uint16_t const _a, uint16_t const _b, uint16_t const _c)
    : a (_a), b (_b), c (_c)
                                                                                                                {}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE>
  LZZ_INLINE mesh <VERT_TYPE, DECL_TYPE>::mesh ()
    : m_vbh (BGFX_INVALID_HANDLE), m_ibh (BGFX_INVALID_HANDLE)
                                                                                       {}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE>
  mesh <VERT_TYPE, DECL_TYPE>::~ mesh ()
                        { destroy(); }
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE>::internal_freeVerts_cb (void * _ptr, void * _userData)
                                                                               {
			BX_UNUSED(_ptr);
			mesh<VERT_TYPE,DECL_TYPE>* sm = (mesh<VERT_TYPE,DECL_TYPE>* )_userData;
			sm->verts.clear();
			}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE>::internal_freeIndicies_cb (void * _ptr, void * _userData)
                                                                                  {
			BX_UNUSED(_ptr);
			mesh<VERT_TYPE,DECL_TYPE>* sm = (mesh<VERT_TYPE,DECL_TYPE>* )_userData;
			sm->indicies.clear();
			}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE>::upload (bool freeOnUploadComplete)
                                                               {
			// Static data can be passed with bgfx::makeRef
			if (freeOnUploadComplete) {
				faces.clear();
				m_vbh = bgfx::createVertexBuffer(
					bgfx::makeRef(verts.data(), sizeof(VERT_TYPE)*verts.size(), internal_freeVerts_cb, this )
					, DECL_TYPE::ms_decl
					);
				m_ibh = bgfx::createIndexBuffer(
					  bgfx::makeRef(indicies.data(), sizeof(uint16_t)*indicies.size(), internal_freeIndicies_cb, this )
					 // , BGFX_BUFFER_INDEX32
					);
				}
			else {
				m_vbh = bgfx::createVertexBuffer(
					bgfx::makeRef(verts.data(), sizeof(VERT_TYPE)*verts.size() )
					, DECL_TYPE::ms_decl
					);
				m_ibh = bgfx::createIndexBuffer(
					  bgfx::makeRef(indicies.data(), sizeof(uint16_t)*indicies.size() )
					 // , BGFX_BUFFER_INDEX32
					);
				}
			}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE>::bind ()
                             {
			bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setIndexBuffer(m_ibh);
			}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE>::destroy ()
                                {
			bgfxh::destroyHandle (m_vbh);
			bgfxh::destroyHandle (m_ibh);
			}
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
// mesh.cpp
//

#define LZZ_INLINE inline
#undef LZZ_INLINE
#endif //BGFXH_IMPL
