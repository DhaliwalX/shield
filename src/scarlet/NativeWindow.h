//
// Created by malcolm on 22/11/17.
//

#ifndef HELLOWORLD_GLWINDOW_H
#define HELLOWORLD_GLWINDOW_H

#include <memory>
#include <SkRefCnt.h>
#include <SkCanvas.h>

class SkSurface;
class SkCanvas;
namespace avenger {

    namespace scarlet {

        struct DrawableArea {
            int width;
            int height;
        };

        class GlContext;

        class NativeWindow {
        public:
            NativeWindow(GlContext *context, int id, uint16_t width, uint16_t height, uint16_t x, uint16_t y);

            static std::shared_ptr<NativeWindow> MakeWindow(GlContext *context);

            static std::shared_ptr<NativeWindow> MakeWindow(GlContext *context,
                                                            uint16_t width,
                                                            uint16_t height,
                                                            uint16_t x,
                                                            uint16_t y);

            void setSurface(sk_sp<SkSurface> surface);


            void setDrawableArea(DrawableArea area);

            const DrawableArea &getDrawableArea() const;

            uint16_t getHeight() { return height; }

            uint16_t getWidth() { return width; }

            uint16_t getX() { return x; }

            uint16_t getY() { return y; }

            void correctScaling();

            SkCanvas *getCanvas();

            void swapBuffers(GlContext *context);

            SkSurface *getSurface();

            sk_sp<SkSurface> createOffScreenCanvas();


            bool shouldQuit() const {
                return shouldQuit_;
            }


            void resizeWindow(int w, int h);

            int getId() const {
                return windowId;
            }

            SkCanvas *getDrawableCanvas();

            void pollEvents();

            void show();

        protected:
            virtual void handleNativeEvents();

        private:
            int windowId;
            uint16_t height;
            uint16_t width;
            uint16_t x;
            uint16_t y;
            bool shouldQuit_ = false;
            GlContext *context;

            DrawableArea drawableArea;

            sk_sp<SkSurface> surface;

            std::unique_ptr<SkBitmap> bitmap;
            // this is the main canvas that will be used to draw all the ui
            std::unique_ptr<SkCanvas> canvas;

            // hack required, as the skia canvas is strangely inverting the image
            SkMatrix operations;
        };

    }
}
#endif //HELLOWORLD_GLWINDOW_H
