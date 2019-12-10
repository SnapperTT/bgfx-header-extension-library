// loadTexture.hh
//

#ifndef LZZ_loadTexture_hh
#define LZZ_loadTexture_hh
#include "bgfxh.h"
/// Note that this file adds a linking dependency on libbimg_decode(Debug/release).a. This is from bimg and is built alongside bgfx 
#define LZZ_INLINE inline
namespace bgfxh
{
  void internal_imageReleaseCb (void * _ptr, void * _userData);
}
namespace bgfxh
{
  bgfx::TextureHandle loadTexture (BGFXH_STRING const & _filename, uint32_t const _flags);
}
namespace bgfxh
{
  bgfx::TextureHandle loadTextureRaw (char const * rawData, uint32_t const rawSize, uint32_t const _flags, char const * textureDbgName = "");
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
#ifndef BGFXH_DOUBLE_GUARD_loadTexture
#define BGFXH_DOUBLE_GUARD_loadTexture
// loadTexture.cpp
//

#include <bimg/decode.h>

#define LZZ_INLINE inline
namespace bgfxh
{
  void internal_imageReleaseCb (void * _ptr, void * _userData)
                                                                  {
		BX_UNUSED(_ptr);
		bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
		bimg::imageFree(imageContainer);
		}
}
namespace bgfxh
{
  bgfx::TextureHandle loadTexture (BGFXH_STRING const & _filename, uint32_t const _flags)
                                                                                               {
		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
	
		BGFXH_STRING rawData;
		bgfxh::readFileRawToString(_filename, rawData);
		if (!rawData.size()) return handle; // File failed to read/is empty
		return loadTextureRaw (&rawData[0], rawData.size(), _flags, _filename.c_str());
		}
}
namespace bgfxh
{
  bgfx::TextureHandle loadTextureRaw (char const * rawData, uint32_t const rawSize, uint32_t const _flags, char const * textureDbgName)
                                                                                                                                                  {
		// Most of this function was adapted from /examples/common/bgfx_utils.cpp, created by Branimir Karadzic.
		/*
		 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
		 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
		 */
		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
		
		bx::Error bErr;
		bimg::ImageContainer * imageContainer = bimg::imageParse(bgfxh::m_allocator, (const void*) rawData, rawSize, bimg::TextureFormat::Count, &bErr);

		if (imageContainer) {
			const bgfx::Memory* mem = bgfx::makeRef(
					  imageContainer->m_data
					, imageContainer->m_size
					, internal_imageReleaseCb
					, imageContainer
					);
				
			if (imageContainer->m_cubeMap) {
				handle = bgfx::createTextureCube(
					  uint16_t(imageContainer->m_width)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
					);
				}
			else if (1 < imageContainer->m_depth) {
				handle = bgfx::createTexture3D(
					  uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, 1 < imageContainer->m_numMips
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
					);
				}
			else if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers, bgfx::TextureFormat::Enum(imageContainer->m_format), _flags) ) {
				handle = bgfx::createTexture2D(
					  uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
					);
				}

			if (bgfx::isValid(handle)) {
				bgfx::setName(handle, textureDbgName);
				}
			}
		
		return handle;
		}
}
#undef LZZ_INLINE
#endif //BGFXH_DOUBLE_GUARD_loadTexture
#endif //BGFXH_IMPL
