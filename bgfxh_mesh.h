// bgfxh_mesh.hh
//

#ifndef LZZ_bgfxh_mesh_hh
#define LZZ_bgfxh_mesh_hh

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
  template <typename VERT_TYPE, typename DECL_TYPE, typename INDEX_TYPE>
  struct mesh
  {
    vector <VERT_TYPE> verts;
    vector <INDEX_TYPE> indicies;
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
  typedef mesh <bx::Vec3, PosVertex, uint16_t> simpleMesh;
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
  template <typename VERT_TYPE, typename DECL_TYPE, typename INDEX_TYPE>
  LZZ_INLINE mesh <VERT_TYPE, DECL_TYPE, INDEX_TYPE>::mesh ()
    : m_vbh (BGFX_INVALID_HANDLE), m_ibh (BGFX_INVALID_HANDLE)
                                                                                       {}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE, typename INDEX_TYPE>
  mesh <VERT_TYPE, DECL_TYPE, INDEX_TYPE>::~ mesh ()
                        { destroy(); }
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE, typename INDEX_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE, INDEX_TYPE>::internal_freeVerts_cb (void * _ptr, void * _userData)
                                                                               {
			BX_UNUSED(_ptr);
			mesh<VERT_TYPE,DECL_TYPE,INDEX_TYPE>* sm = (mesh<VERT_TYPE,DECL_TYPE,INDEX_TYPE>* )_userData;
			sm->verts.clear();
			}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE, typename INDEX_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE, INDEX_TYPE>::internal_freeIndicies_cb (void * _ptr, void * _userData)
                                                                                  {
			BX_UNUSED(_ptr);
			mesh<VERT_TYPE,DECL_TYPE,INDEX_TYPE>* sm = (mesh<VERT_TYPE,DECL_TYPE,INDEX_TYPE>* )_userData;
			sm->indicies.clear();
			}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE, typename INDEX_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE, INDEX_TYPE>::upload (bool freeOnUploadComplete)
                                                               {
			// Static data can be passed with bgfx::makeRef
			if (freeOnUploadComplete) {
				faces.clear();
				m_vbh = bgfx::createVertexBuffer(
					bgfx::makeRef(verts.data(), sizeof(VERT_TYPE)*verts.size(), internal_freeVerts_cb, this )
					, DECL_TYPE::ms_decl
					);
				if (sizeof(INDEX_TYPE) == sizeof(uint32_t))
					m_ibh = bgfx::createIndexBuffer( bgfx::makeRef(indicies.data(), sizeof(INDEX_TYPE)*indicies.size(), internal_freeIndicies_cb, this ), BGFX_BUFFER_INDEX32);
				else
					m_ibh = bgfx::createIndexBuffer( bgfx::makeRef(indicies.data(), sizeof(INDEX_TYPE)*indicies.size(), internal_freeIndicies_cb, this ));
				}
			else {
				m_vbh = bgfx::createVertexBuffer(
					bgfx::makeRef(verts.data(), sizeof(VERT_TYPE)*verts.size() )
					, DECL_TYPE::ms_decl
					);
				if (sizeof(INDEX_TYPE) == sizeof(uint32_t))
					m_ibh = bgfx::createIndexBuffer( bgfx::makeRef(indicies.data(), sizeof(INDEX_TYPE)*indicies.size() ), BGFX_BUFFER_INDEX32 );
				else
					m_ibh = bgfx::createIndexBuffer( bgfx::makeRef(indicies.data(), sizeof(INDEX_TYPE)*indicies.size() ));
				}
			}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE, typename INDEX_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE, INDEX_TYPE>::bind ()
                             {
			bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setIndexBuffer(m_ibh);
			}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE, typename INDEX_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE, INDEX_TYPE>::destroy ()
                                {
			bgfxh::destroyHandle (m_vbh);
			bgfxh::destroyHandle (m_ibh);
			}
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
#ifndef BGFXH_DOUBLE_GUARD_bgfxh_mesh
#define BGFXH_DOUBLE_GUARD_bgfxh_mesh
// bgfxh_mesh.cpp
//

#define LZZ_INLINE inline
#undef LZZ_INLINE
#endif //BGFXH_DOUBLE_GUARD_bgfxh_mesh
#endif //BGFXH_IMPL
