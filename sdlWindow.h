// sdlWindow.hh
//

#ifndef LZZ_sdlWindow_hh
#define LZZ_sdlWindow_hh
struct SDL_Window;
#define LZZ_INLINE inline
namespace bgfxh
{
  bool initSdlWindow (SDL_Window * _window);
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

#include <SDL2/SDL_syswm.h> //Needed for window handling
#define LZZ_INLINE inline
namespace bgfxh
{
  bool initSdlWindow (SDL_Window * _window)
                                                  {
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi) ) {
			return false;
			}

		bgfx::PlatformData pd;
		#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
			pd.ndt          = wmi.info.x11.display;
			pd.nwh          = (void*)(uintptr_t)wmi.info.x11.window;
		#elif BX_PLATFORM_OSX
			pd.ndt          = NULL;
			pd.nwh          = wmi.info.cocoa.window;
		#elif BX_PLATFORM_WINDOWS
			pd.ndt          = NULL;
			pd.nwh          = wmi.info.win.window;
		#elif BX_PLATFORM_STEAMLINK
			pd.ndt          = wmi.info.vivante.display;
			pd.nwh          = wmi.info.vivante.window;
		#endif // BX_PLATFORM_
		pd.context      = NULL;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		bgfx::setPlatformData(pd);
		return true;
		}
}
namespace bgfxh
{
  bool initSdlWindowAndBgfx (SDL_Window * _window, bgfx::Init * _init)
                                                                                    {
		if (!initSdlWindow (_window))
			return false;
			
		int ww;
		int wh;
		SDL_GetWindowSize(_window, &ww, &wh);
		
		const uint32_t m_resetFlags = BGFX_RESET_VSYNC | BGFX_RESET_MAXANISOTROPY | BGFX_RESET_FLIP_AFTER_RENDER ;// | BGFX_RESET_MSAA_X4;
		
		//bgfx::renderFrame();
		
		bool initSet = (_init);
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
