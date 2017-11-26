//
// Created by malcolm on 22/11/17.
//

#include "NativeWindow.h"
#include "GlContext.h"

#include <SkSurface.h>
#include <SDL2/SDL_events.h>

namespace avenger {

    namespace scarlet {
        std::shared_ptr<NativeWindow> NativeWindow::MakeWindow(GlContext *context) {
            return context->makeWindow();
        }

        std::shared_ptr<NativeWindow>
        NativeWindow::MakeWindow(GlContext *context, uint16_t width, uint16_t height, uint16_t x, uint16_t y) {
            return context->makeWindow(width, height, x, y);
        }

        NativeWindow::NativeWindow(GlContext *context, int id, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
                : windowId{id}, width{width}, height{height}, x{x}, y{y}, context{context} {
        }

        void NativeWindow::setSurface(sk_sp<SkSurface> surface) {
            this->surface = std::move(surface);
        }

        SkCanvas *NativeWindow::getCanvas() {
            return surface->getCanvas();
        }

        SkSurface *NativeWindow::getSurface() {
            return surface.get();
        }

        void NativeWindow::setDrawableArea(DrawableArea area) {
            drawableArea = area;

            // these operations invert the image along the x axis
            operations.reset();
            operations.setScale(1, -1);
            operations.postTranslate(0, area.height);

            // initialize SkCanvas here
            auto info = SkImageInfo::MakeN32Premul(area.width, area.height);
            bitmap = std::make_unique<SkBitmap>();
            bitmap->allocPixels(info);
            canvas = std::make_unique<SkCanvas>(*bitmap);
            canvas->concat(operations);
        }

        const DrawableArea &NativeWindow::getDrawableArea() const {
            return drawableArea;
        }

        void NativeWindow::correctScaling() {
            getCanvas()->scale((float) width / drawableArea.width, (float) height / drawableArea.height);
        }

        void NativeWindow::swapBuffers(GlContext *context) {
            context->swapBuffers(windowId);
        }


        sk_sp<SkSurface> NativeWindow::createOffScreenCanvas() {
            auto colorSpace = SkColorSpace::MakeSRGB();
            SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);

            auto imageInfo = SkImageInfo::Make(getHeight(),
                                               getWidth(),
                                               SkColorType::kBGRA_8888_SkColorType,
                                               SkAlphaType::kPremul_SkAlphaType,
                                               colorSpace);

            auto surface = SkSurface::MakeRaster(imageInfo, &props);

            SkASSERT(surface);
            return surface;
        }

        void NativeWindow::resizeWindow(int w, int h) {
            SkASSERT(context);
            context->resizeWindow(this, w, h);
        }

        void NativeWindow::handleNativeEvents() {
            SDL_Event event;
            int w, h;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_MOUSEMOTION:
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        break;
                    case SDL_KEYDOWN: {
                        break;
                    }

                    case SDL_WINDOWEVENT: {
                        SDL_Window *window = SDL_GetWindowFromID(event.window.windowID);

                        if (window != nullptr && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                            SDL_GL_GetDrawableSize(window, &w, &h);
                            resizeWindow(w, h);
#ifdef SK_DEBUG
                            context->printDebugInfo(this);
#endif
                        }
                        break;
                    }
                    case SDL_QUIT:
                        shouldQuit_ = true;
                        break;
                    default:
                        break;
                }
            }
        }

        void NativeWindow::pollEvents() {
            handleNativeEvents();
        }

        void NativeWindow::show() {
            SkASSERT(surface);
            SkASSERT(context);

            surface->getCanvas()->drawBitmap(*bitmap, 0, 0);
            swapBuffers(context);
        }

        SkCanvas *NativeWindow::getDrawableCanvas() {
            return canvas.get();
        }

    }
}
