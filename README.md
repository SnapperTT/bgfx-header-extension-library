Bgfx Header Utils Extension Library
===================================
An extension library for [bgfx](https://github.com/bkaradzic/bgfx) to help you hit the ground running by wrapping common tasks in simple header files. It also provides a number of RenderJobs to provide an off-the-shelf solution to common rendering demands, such as post processing filters, shadow mapping and more.

Like bgfx, this is rendering library. Its not a game engine and does not aim to be. Rather it simply gives you the pieces to rapidly assemble a graphics pipeline in a cross platform, api agnostic manner. Bgfxh aims to bridge the gap between using a potentially large or bloated generalist graphics library or game engine for simple rendering jobs, and reinventing the wheel by creating an engine from scratch. By thinly relying on bgfx maintenance requirements are kept low. 

## Contact:
@SnapperTheTwig

## Features:
* Header only library, inspired by [stb](https://github.com/nothings/stb), requires no changes to your build system. Simply use #define BGFXH_IMPL before #include to generate an implementation
* Only pay for what you use. Don't want texture loading? Then don't `#include <bgfxh/loadTexture.h>`. Only want it
* SDL Window management with `initSdlWindow()`
* Texture Loading with `loadTexture()` - supports what [bimg](https://github.com/bkaradzic/bimg) supports (most of this is extracted from the bgfx examples and repackaged to be used here)
* Shader Loading with `loadShader()`
* Inspect textures/framebuffers with `debugDrawFramebuffer()` and `debugDrawFramebufferMono()` for monochromatic framebuffers (such as depth buffers). 
* Frustum culling utility
* A variety of RenderJobs, see below for more info
* Thin layer ontop of bgfxh. Rather than hiding the underlying framework under a complex layer of abstraction, bgfxh just provides free functions that do some job. RenderJobs are c++ classes, are optional
* Few dependencies - only on bgfx/bimg/bx and some standard c/c++ libraries
* Permissive license

## RenderJobs:
RenderJobs are basically C++ objects that wrap bgfx commands and resources do some graphical task. To use, simply:
* Include the relevant file (eg `#include <bgfxh/renderJobs/bloom.h>`)
* Create an object `bgfxh::bloomRenderJob mBloomRenderJob;`
* Choose your settings for the filter, then call `mBloomRenderJob.init();` - this generates the uniforms, samplers and framebuffers for the filter and loads the relevant shaders
* In your rendering loop, call `mBloomRenderJob.submit(framebufferToBloom);` - this will set up the views
* On object destruction all resources created will be freed.

Shaders ''can'' be embedded in the RenderJobs. Use `#define BGFXH_EMBED_FILTER_SHADERS` to embed at compile time.

Each filter has detailed use instructions in the top of their respective header file.

Availiable RenderJobs:
* `cascadingShadowMap.h` - Cascading shadowmap generation (both regular and VSM, with frustum checking)
* `bloom.h` - Bloom with a fixed gaussian kernal. Uses bilinear filtering for efficiency
* `lum.h` - Time averaged luminance calculation
* `tonemapping.h` - ACES Filmic Tonemapping + can combine the outputs of other RenderJobs

## Shaders:
Simply copy the shaders you want and merge the folders together. So to add bloom and luminance shaders to your application copy the contents of `bgfxh/shaders/bloom/` and `bgfx/shaders/lum/` to `yourApp/<yourShaderPath>/`, and set `bgfxh::shaderSearchPath` to `"<yourShaderPath>/" + bgfxh::getShaderDirectoryFromRenderType() + "/"` to point the shader loader to the right shaders. For OpenGl this will be `"<yourShaderPath>/glsl/"`, for dx11 this will be `"<yourShaderPath>/dx11/"`, for Vulkan this will be `"<yourShaderPath>/spriv/"`

Note that `bgfxh::shaderSearchPath` only effects the location of shaders loaded for bgfxh filters! Eg bgfxh::bloomRenderJob will load `bloom_brightpass` by invoking `bgfxh::loadShader(bgfxh::shaderSearchPath + "vs_bloom_brightpass.bin", bgfxh::shaderSearchPath + "fs_bloom_brightpass.bin")`

loadShader will handle Windows or POSIX file paths (it internally invokes `bgfxh::fixPath(path)`)

If you are lacking a build system for your own shaders you can use the one provided.

Shaders come already compiled + are embeddable, so you can use them right away!

## Contributing:
More Render Jobs = more better! I do have plans to specifically make the following, but any input will be greatly appreciated
* A light sprite/tile engine (sprites should use the transient buffer, tiles should use a vertex buffer).
* Screenspace reflection
* A simple forward renderer

Be sure to create/edit the `.lzz` files, not the generated `.h` files. The tools + scripts to create the header files from the `.lzz` sources are provided.

How Do I?
=========

## Create a SDL Window?
```c++
#include <SDL>
#include <bgfx>

#define BGFXH_IMPL
#include <bfgxh/bgfxh.h>
#include <bfgxh/sdlWindow.h>

int main (int argc, char *argv[]) {
	SDL_Init(0);
	SDL_Window * mWindow = SDL_CreateWindow("BGFXH Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	bgfxh::initSdlWindowAndBgfx(mWindow); // Creates a bgfx context in an sdl window
	
	// You now have a window + a bgfx context!
	while (true) {
		drawStuff();
		bgfx::frame();
		}
	}
```

`initSdlWindowAndBgfx()` internally calls `bgfx::init()` with some default parameters. You can avoid this by calling `initSdlWindow(mWindow);`, then call `bgfx::init();` when you like;

## Load a Texture? (.dds/.ktx) Or an Image as a Texture (.jpg, .png, .tga, etc).
```c++
#define BGFXH_IMPL
#include <bfgxh/loadTexture.h>

...

bgfx::TextureHandle foo = bgfxh::loadTexture ("filename.ext", BGFX_TEXTURE_FLAGS | BGFX_SAMPLER_FLAGS);

```

**NOTE:** that this file adds a linking dependency on libbimg_decode(Debug/release).a. This is from bimg and is built alongside bgfx

It is recommended that you use texturec (part of bgfx, see tools) to create a texture file (.dds/.kxt) as these are optimised for loading and can contain pre-computed mipmaps. On the fly mipmap generation is not supported (and is slow anyway).

## Initialise BGFX and BGFXH?
```c++
#define BGFXH_IMPL
#include <bfgxh/bgfxh.h>
#include <bfgxh/sdlWindow.h> // If using SDL Windows!

...

initSdlWindow(mWindow);
bgfxh::init(backbufferWidth, backbufferHeight, "path/to/shaders"); //<-- shaders, uniforms and vertexDecl's for debug drawing are made here

.... OR ....

bgfx::Init mInit;
// Set mInit's parameters here
initSdlWindow(mWindow, mInit);
bgfxh::init(backbufferWidth, backbufferHeight, "path/to/shaders"); //<-- shaders, uniforms and vertexDecl's for debug drawing are made here

.... OR ....

initSdlWindow(mWindow, NULL, false); // Don't call bgfx::init() internally. Infact if you're not using SDL you can omit this line altogether
bgfx::init();
bgfxh::init(backbufferWidth, backbufferHeight, "path/to/shaders");
```

## View the Contents of a Framebuffer?
```c++
#define BGFXH_IMPL
#include <bfgxh/bgfxh.h>

...

bgfx::init();
bgfxh::init(backbufferWidth, backbufferHeight, "path/to/shaders"); //<-- shaders, uniforms and vertexDecl's for debug drawing are made here

...

// Initialises a 2D view, with tag, size, no framebuffer attachement (render to backbuffer), doesn't clear, and is not a unit ortho matrix 
bgfxh::initView2D (VIEW_ID_OUTPUT_PASS, "output pass", backbufferWidth, backbufferHeight, BGFX_INVALID_HANDLE, false, false);
// Viewing a texture
// ViewId, thingToInspect, xPos, yPos, xSize, ySize, (backbufferWidth), (backbufferHeight)
// (backbufferWidth), (backbufferHeight) are only used for pixel-perfect dx9 rendering and can be ommitted if you don't care about that
bgfxh::debugDrawTexture (VIEW_ID_OUTPUT_PASS, textureHandleToView, 10, 10, 120, 120, backbufferWidth, backbufferHeight); 

// Viewing a framebuffer
bgfxh::debugDrawFramebuffer (VIEW_ID_OUTPUT_PASS, framebufferToInspect, 10+130, 10, 120, 120, backbufferWidth, backbufferHeight);

// Viewing the output of a bgfxh::renderJob
bgfxh::debugDrawFramebuffer (VIEW_ID_OUTPUT_PASS, mBgfxhLumRenderJob.getOutputFramebuffer(), 10+130*2, 10, 120, 120, backbufferWidth, backbufferHeight);

// Inspecting a cascading shadow map (eg, cascadingShadowMapRenderJob.h)
for (unsigned int i = 0; i < mBgfxhCsmRenderJob.nShadowLevels; ++i)
	bgfxh::debugDrawFramebuffer (VIEW_ID_OUTPUT_PASS, mBgfxhCsmRenderJob.getOutputFramebuffer(i), 10 + 130*i, 130, 120, 120, backbufferWidth, backbufferHeight);
		
```

## Create a Rendering Pipeline With The Provided RenderJobs and My Stuff?
```c++
#define BGFXH_IMPL
#include <bfgxh/bgfxh.h>
// Optionally #define BGFXH_EMBED_RENDER_JOB_SHADERS if you want shaders embedded at compile time
#include <bfgxh/renderJobs/bloom.h>
#include <bfgxh/renderJobs/lum.h>

class GfxPipeline {
public:
	// RenderJob objects
	bgfxh::bloomRenderJob mBloomRenderJob; // Each "job" or is a class! 
	bgfxh::lumRenderJob mLumRenderJob;
	bgfxh::tonemappingRenderJob mTonemappingRenderJob;
	// Your resources
	bgfx::ProgramHandle m_myProgram;
	bgfx::FrameBufferHandle m_myFramebuffer;

	GfxPipeline () {}
	~GfxPipeline() {} // Each "job" will clean up its resources on destruction

	void init () {
		// Set parameters
		mBloomRenderJob.setSize (600, 360);
		mBloomRenderJob.nBloomBlurPasses = 2;
		mBloomRenderJob.init(); // Resources are created here!
		mLumRenderJob.init();
		
		mTonemappingRenderJob.setSize (1200, 720);
		mTonemappingRenderJob.maxAdditonalSamplerSlots = 1; // Configure the tonemapping filter to accept a blended attachement
		mTonemappingRenderJob.init ();
		
		// Your stuff
		m_myProgram = bgfxh::loadProgram("path/vs_forwardRenderer.bin", "fs_forwardRenderer.bin");
		m_myFramebuffer = ... ; // Gbuffer? Or just a colour/depth buffer for forward rendering!
		
		}
		
	void submitScene (YourScene) {
		mLumRenderJob.viewId = 1; // A lum filter will take up 5 views
		mBloomRenderJob.viewId = 1 + mLumRenderJob.getViewIncrement();  // A bloom filter will take a number of views depending on how many blur passes you are doing
		mTonemappingRenderJob.viewId = mBloomRenderJob.viewId + mBloomRenderJob.getViewIncrement();
		
		...
		// Render your scene to a framebuffer (m_myFramebuffer)
		// You still have to implement your own forward or gbuffer here
		//bgfx::submit(0, m_myProgram)
		
		...
		// Apply Post Processing using the filters!
		mLumRenderJob.submit (bgfx::getTexture(m_myFramebuffer, 0));
		// Get the output of a renderJob as a texture that you can use in another renderJob!
		mBloomRenderJob.submit (mLumRenderJob.getOutputTexture(), bgfx::getTexture(m_myFramebuffer, 0)); 
		// Configure the tonemapping filter to additively blend the bloom
		mBgfxhTonemappingRenderJob.setExtraComponent (0, mBgfxhBloomRenderJob.getOutputTexture(), 1.0f, 0.f);
		// Does the tonemapping. Renders to backbuffer by default
		mTonemappingRenderJob.submit (bgfx::getTexture(m_myFramebuffer, 0), mLumRenderJob.getOutputTexture()); 
		
		// Debug render the lum filter's output to see if it is calculating sensible lum values
		const int OUTPUT_PASS_ID = 200;
		bgfxh::initView2D (VIEW_ID_OUTPUT_PASS, "output pass", backbufferWidth, backbufferHeight, BGFX_INVALID_HANDLE, false, false);
		bgfxh::debugDrawFramebuffer (VIEW_ID_OUTPUT_PASS, mLumRenderJob.getOutputFramebuffer(), 10, 10, 120, 120, backbufferWidth, backbufferHeight);
		}
		
		
	}

```

## Speed Up Compile Times By Making A Seperate Compilation Unit?
```c++
//Wrapper.h
#include <bfgxh/bgfxh.h>
#include <bfgxh/...>
#include <bfgxh/...> //etc
```
```c++
//Wrapper.cpp
#define BGFXH_IMPL
#include <bfgxh/bgfxh.h>
#include <bfgxh/...>
#include <bfgxh/...> //etc
```

## Frustum Cull?
```c++
#define BGFXH_IMPL
#include <bfgxh/bgfxh.h>

...

bgfxh::frustum mFrustum;
mFrustum.setFromViewAndProjMatrix (viewMtx, projMtx);

for (each object in scene) {
	if (mFrustum.frustumCheck (object.positionVec3, object.radius)) continue; // Where radius is the radius of some bounding sphere for the object
	... Alternatively ....
	if (mFrustum.frustumCheck (object.bgfxModelMtx, object.radius)) continue;
	// Set uniforms, transform matricies, etc
	bgfx::setTransform (object.bgfxModelMtx);
	bgfx::submit();
	}


```

Thanks
======
Thanks To Branimir Karadzic and all others who have contributed to Bgfx!

License
=======
Public Domain
Various code snippets have been adapted from bgfx and are thus under the BSD license.
