//
// Created by malcolm on 22/11/17.
//

#include "GlContext.h"
#include <SDL2/SDL.h>
#include "gl/GrGLInterface.h"
#include "gl/GrGLUtil.h"
#include "GrBackendSurface.h"
#include "GrContext.h"
#include "SkWindow.h"
#include "SkSurface.h"

#include <map>
#include <GL/glu.h>
namespace avenger {
    namespace scarlet {
        struct NativeWindowInternal {
            SDL_Window *window = nullptr;
            SDL_GLContext context = nullptr;
        };

        void handleError() {
            printf("Error: SDLError: %s\n", SDL_GetError());
        }

        void makeWindowForGL(NativeWindowInternal *wrapper, NativeWindow *glWindow) {
            SDL_GLContext glContext = nullptr;

            glContext = SDL_GL_CreateContext(wrapper->window);
            if (glContext == nullptr) {
                // TODO: do return error;
                handleError();
                exit(-1);
            }

            wrapper->context = glContext;
            int success = SDL_GL_MakeCurrent(wrapper->window, glContext);
            if (success != 0) {
                handleError();
                exit(1);
            }

            int w, h;
            DrawableArea area;

            SDL_GL_GetDrawableSize(wrapper->window, &w, &h);
            glViewport(0, 0, w, h);
            glClearColor(1, 1, 1, 1);
            glClearStencil(0);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            area.width = w;
            area.height = h;

            sk_sp<const GrGLInterface> interface(GrGLCreateNativeInterface());
            sk_sp<GrContext> grContext(GrContext::MakeGL(interface.get()));
            SkASSERT(grContext);

            // wrap a frame buffer to the screen in a skia render target
            GrGLint buffer;
            GR_GL_GetIntegerv(interface.get(), GR_GL_FRAMEBUFFER_BINDING, &buffer);
            GrGLFramebufferInfo info;
            info.fFBOID = static_cast<GrGLuint>(buffer);
            GrBackendRenderTarget renderTarget(w, h, 0, 8, kSkia8888_GrPixelConfig, info);

            // setup SkSurface
            SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);

            sk_sp<SkSurface> surface(SkSurface::MakeFromBackendRenderTarget(grContext.get(), renderTarget,
                                                                            kTopLeft_GrSurfaceOrigin,
                                                                            nullptr, &props));

            SkASSERT(surface);
            glWindow->setSurface(surface);
            glWindow->setDrawableArea(area);
        }

        class NativeWindowFactory {
        public:
            std::shared_ptr<NativeWindow>
            createWindow(GlContext *context, const std::string &title, uint16_t width, uint16_t height, uint16_t x,
                         uint16_t y) {
                uint32_t windowFlags = 0;
                windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
                SDL_Window *window = SDL_CreateWindow(title.c_str(),
                                                      SDL_WINDOWPOS_CENTERED,
                                                      SDL_WINDOWPOS_CENTERED,
                                                      width,
                                                      height, windowFlags);

                std::shared_ptr<NativeWindowInternal> nativeWindow = std::make_shared<NativeWindowInternal>();

                nativeWindow->window = window;
                int id = saveWindow(nativeWindow);
                std::shared_ptr<NativeWindow> glWindow = std::make_shared<NativeWindow>(context, id, width, height, x,
                                                                                        y);
                makeWindowForGL(nativeWindow.get(), glWindow.get());

                // correct the scaling
                glWindow->correctScaling();
                return glWindow;
            }

            std::shared_ptr<NativeWindowInternal> getNativeWindow(int id) {
                auto window = windows_.find(id);
                if (window != windows_.end()) {
                    return window->second;
                }

                return nullptr;
            }

            static NativeWindowFactory *getInstance() {
                return factory_.get();
            }

            static void destroy() {
                factory_->destroyWindows();
            }

        private:

            void destroyWindows() {
                for (auto p : windows_) {
                    auto window = p.second;
                    if (window->context != nullptr) {
                        SDL_GL_DeleteContext(window->context);
                    }
                    SDL_DestroyWindow(window->window);
                }
            }

            // single instance of the factory
            static std::unique_ptr<NativeWindowFactory> factory_;

            int saveWindow(std::shared_ptr<NativeWindowInternal> window) {
                static int counter = 0;

                windows_.insert({counter++, window});

                return counter - 1;
            }

            std::map<int, std::shared_ptr<NativeWindowInternal>> windows_;
        };

        std::unique_ptr<NativeWindowFactory> NativeWindowFactory::factory_ = std::make_unique<NativeWindowFactory>();

        std::shared_ptr<NativeWindow> GlContext::makeWindow(uint16_t width, uint16_t height, uint16_t x, uint16_t y) {
            return windowFactory_->createWindow(this, "Captain", width, height, x, y);
        }

        std::shared_ptr<NativeWindow> GlContext::makeWindow() {
            return makeWindow(screenDesc.getWidth(), screenDesc.getHeight(), 0, 0);
        }

        std::shared_ptr<GlContext> GlContext::Make(int *argc, char **argv) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            // For all other clients we use the core profile and operate in a window
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


            static const int kStencilBits = 8;  // Skia needs 8 stencil bits
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, kStencilBits);

            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

            static const int kMsaaSampleCount = 0; //4;

            /*
             * In a real application you might want to initialize more subsystems
             */
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
                return nullptr;
            }

            // Setup window
            // This code will create a window with the same resolution as the user's desktop.
            SDL_DisplayMode dm;
            if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
                return nullptr;
            }

            ScreenDesc desc((uint16_t) dm.w, (uint16_t) dm.h);
            return std::make_shared<GlContext>(desc, NativeWindowFactory::getInstance());
        }

        GlContext::~GlContext() {
            // destroy the windows
            NativeWindowFactory::destroy();
            SDL_Quit();
        }

        void GlContext::swapBuffers(int windowId) {
            auto nativeWindow = windowFactory_->getNativeWindow(windowId);
            SDL_GL_SwapWindow(nativeWindow->window);
        }

        void GlContext::resizeWindow(NativeWindow *window, int w, int h) {
            screenDesc.setHeight(h);
            screenDesc.setWidth(w);
            auto nativeWindow = windowFactory_->getNativeWindow(window->getId());
            window->setDrawableArea({w, h});
            // TODO: inform other data structures about window resize
        }

        void GlContext::printDebugInfo(NativeWindow *window) {
            SDL_DisplayMode mode;
            SDL_Rect rect;
            auto win = windowFactory_->getNativeWindow(window->getId())->window;
            SDL_GetWindowDisplayMode(win, &mode);

            printf("Display specs: %dx%d\n", mode.w, mode.h);
        }
    }
}