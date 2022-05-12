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
    vector <INDEX_TYPE> indices;
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
			vector<VERT_TYPE>* vertsHeap = (vector<VERT_TYPE>*)_userData;
			delete vertsHeap;
			}
}
namespace bgfxh
{
  template <typename VERT_TYPE, typename DECL_TYPE, typename INDEX_TYPE>
  void mesh <VERT_TYPE, DECL_TYPE, INDEX_TYPE>::internal_freeIndicies_cb (void * _ptr, void * _userData)
                                                                                  {
			BX_UNUSED(_ptr);
			vector<INDEX_TYPE>* indicesHeap = (vector<INDEX_TYPE>*)_userData;
			delete indicesHeap;
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
				
				vector<VERT_TYPE>* vertsHeap = new vector<VERT_TYPE>;
				vector<INDEX_TYPE>* indicesHeap = new vector<INDEX_TYPE>;
				vertsHeap->swap(verts);
				indicesHeap->swap(indices);
				
				m_vbh = bgfx::createVertexBuffer(
					bgfx::makeRef(vertsHeap->data(), sizeof(VERT_TYPE)*vertsHeap->size(), internal_freeVerts_cb, vertsHeap )
					, DECL_TYPE::ms_decl
					);
				if (sizeof(INDEX_TYPE) == sizeof(uint32_t))
					m_ibh = bgfx::createIndexBuffer( bgfx::makeRef(indicesHeap->data(), sizeof(INDEX_TYPE)*indicesHeap->size(), internal_freeIndicies_cb, indicesHeap ), BGFX_BUFFER_INDEX32);
				else
					m_ibh = bgfx::createIndexBuffer( bgfx::makeRef(indicesHeap->data(), sizeof(INDEX_TYPE)*indicesHeap->size(), internal_freeIndicies_cb, indicesHeap ));
				}
			else {
				m_vbh = bgfx::createVertexBuffer(
					bgfx::makeRef(verts.data(), sizeof(VERT_TYPE)*verts.size() )
					, DECL_TYPE::ms_decl
					);
				if (sizeof(INDEX_TYPE) == sizeof(uint32_t))
					m_ibh = bgfx::createIndexBuffer( bgfx::makeRef(indices.data(), sizeof(INDEX_TYPE)*indices.size() ), BGFX_BUFFER_INDEX32 );
				else
					m_ibh = bgfx::createIndexBuffer( bgfx::makeRef(indices.data(), sizeof(INDEX_TYPE)*indices.size() ));
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
