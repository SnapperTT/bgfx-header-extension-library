// sdlWindow.cpp
//

#include "sdlWindow.hh"
#ifndef BGFXH_SDL_SYSWM_HANDLED
	#include <SDL2/SDL_syswm.h> //Needed for window handling
#endif
#define LZZ_INLINE inline
namespace bgfxh
{
  void * getSdlNativeWindowHandle (SDL_Window * _window)
                                                            {
		// From bgfx/examples/common/entry_sdl.cpp
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi) ) {
			return NULL;
			}

		#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
		#		if BGFXH_USE_WAYLAND
				wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
				if(!win_impl)
				{
					int width, height;
					SDL_GetWindowSize(_window, &width, &height);
					struct wl_surface* surface = wmi.info.wl.surface;
					if(!surface)
						return nullptr;
					win_impl = wl_egl_window_create(surface, width, height);
					SDL_SetWindowData(_window, "wl_egl_window", win_impl);
				}
				return (void*)(uintptr_t)win_impl;
		#		else
				return (void*)wmi.info.x11.window;
		#		endif
		#	elif BX_PLATFORM_OSX || BX_PLATFORM_IOS
				return wmi.info.cocoa.window;
		#	elif BX_PLATFORM_WINDOWS
				return wmi.info.win.window;
		#   elif BX_PLATFORM_ANDROID
				return wmi.info.android.window;
		#	endif // BX_PLATFORM_
		}
}
namespace bgfxh
{
  void * getNativeDisplayHandle (SDL_Window * _window)
                                                          {
		// From bgfx/examples/common/entry_sdl.cpp
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi) ) {
			return NULL;
			}

		#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
		#		if BGFXH_USE_WAYLAND
				return wmi.info.wl.display;
		#		else
				return wmi.info.x11.display;
		#		endif // ENTRY_CONFIG_USE_WAYLAND
		#	else
				return NULL;
		#	endif // BX_PLATFORM_*
		}
}
namespace bgfxh
{
  bool initSdlWindow (SDL_Window * _window, bgfx::PlatformData & pdOut)
                                                                              {
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi) ) {
			return false;
			}
			
		pdOut.nwh = bgfxh::getSdlNativeWindowHandle(_window);
		pdOut.ndt = bgfxh::getNativeDisplayHandle(_window);
		
		pdOut.context      = NULL;
		pdOut.backBuffer   = NULL;
		pdOut.backBufferDS = NULL;
		return true;
		}
}
namespace bgfxh
{
  bool initSdlWindowAndBgfx (SDL_Window * _window, bgfx::Init * _init)
                                                                                    {
		bgfx::PlatformData pd;
		if (!initSdlWindow (_window, pd))
			return false;
			
		int ww;
		int wh;
		SDL_GetWindowSize(_window, &ww, &wh);
		
		const uint32_t m_resetFlags = BGFX_RESET_VSYNC | BGFX_RESET_MAXANISOTROPY | BGFX_RESET_FLIP_AFTER_RENDER ;// | BGFX_RESET_MSAA_X4;
		
		//bgfx::renderFrame();
		
		//bool initSet = (_init);
		if (!_init) {
			bgfx::Init init;
			init.type     = bgfx::RendererType::Count;
			//init.type     = bgfx::RendererType::OpenGL;
			init.vendorId = BGFX_PCI_ID_NONE;
			init.debug  = true;
			init.resolution.width  = ww;
			init.resolution.height = wh;
			init.resolution.reset  = m_resetFlags;
			_init = &init;
			}
			
		_init->platformData = pd;
		
		bgfx::init(*_init);
		bgfx::reset(ww,wh, _init->resolution.reset);

		// Enable debug text.
		if (_init->debug)
			bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_WIREFRAME);

		// Set view 0 clear state.
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
			);
			
		return true;
		}
}
#undef LZZ_INLINE
