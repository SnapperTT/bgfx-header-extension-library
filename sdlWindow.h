// sdlWindow.hh
//

#ifndef LZZ_sdlWindow_hh
#define LZZ_sdlWindow_hh
struct SDL_Window;
#define LZZ_INLINE inline
namespace bgfxh
{
  bool getSdlNativeWindowHandles (SDL_Window * _window, bgfx::PlatformData & pdOut);
}
namespace bgfxh
{
  bool initSdlWindow (SDL_Window * _window, bgfx::PlatformData & pdOut);
}
namespace bgfxh
{
  bool initSdlWindowAndBgfx (SDL_Window * _window, bgfx::Init * _init = NULL);
}
#undef LZZ_INLINE
#endif

////////////////////////////////////////////////////////////////////////

#ifdef BGFXH_IMPL
#ifndef BGFXH_DOUBLE_GUARD_sdlWindow
#define BGFXH_DOUBLE_GUARD_sdlWindow
// sdlWindow.cpp
//

#define LZZ_INLINE inline
namespace bgfxh
{
  bool getSdlNativeWindowHandles (SDL_Window * _window, bgfx::PlatformData & pdOut)
                                                                                        {
		// https://gist.github.com/ShogunateTM/87947e63ccb8ae273c85fbfc5f6f03b0
		// writes nwh and ndt in pdOut
		#if defined(SDL_PLATFORM_WIN32)
			pdOut.nwh = SDL_GetPointerProperty( SDL_GetWindowProperties( _window ), SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL );
			pdOut.ndt = NULL;
			return true;
		#elif defined(SDL_PLATFORM_MACOS)
			pdOut.nwh = SDL_GetPointerProperty( SDL_GetWindowProperties( _window ), SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, NULL );
			pdOut.ndt = NULL;
			return true;
		#elif defined(SDL_PLATFORM_LINUX)
			if( SDL_strcmp( SDL_GetCurrentVideoDriver(), "x11" ) == 0 ) 
			{
				pdOut.ndt = SDL_GetPointerProperty( SDL_GetWindowProperties( _window ), SDL_PROP_WINDOW_X11_DISPLAY_POINTER, NULL );
				pdOut.nwh = (void*) SDL_GetNumberProperty( SDL_GetWindowProperties( _window  ), SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0 );
				return true;
			}
			else if( SDL_strcmp( SDL_GetCurrentVideoDriver(), "wayland" ) == 0 ) 
			{
				/*struct wl_display *display*/ pdOut.ndt = SDL_GetPointerProperty( SDL_GetWindowProperties( _window ), SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, NULL );
				/*struct wl_surface *surface*/ pdOut.nwh = SDL_GetPointerProperty( SDL_GetWindowProperties( _window ), SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, NULL );
				return true;
			}
		#endif
		return false;
		}
}
namespace bgfxh
{
  bool initSdlWindow (SDL_Window * _window, bgfx::PlatformData & pdOut)
                                                                              {
		bool r = bgfxh::getSdlNativeWindowHandles(_window, pdOut);
		if (!r) return false; // failed to get native handles
		
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
#endif //BGFXH_DOUBLE_GUARD_sdlWindow
#endif //BGFXH_IMPL
