#include <iostream>

#include "../scarlet/GlContext.h"

#include "GrBackendSurface.h"
#include "GrContext.h"
#include "SkWindow.h"
#include "SkSurface.h"
#include "../spidey/MatToBitmapConvertor.h"
#include "Captain.h"

#include <thread>
#include <opencv2/videoio.hpp>
#include <SkImageDeserializer.h>
#include <opencv/cv.hpp>

#undef SK_DEBUG
#ifndef SK_DEBUG
bool gLogCallsGL = false;
bool gCheckErrorGL = false;
#endif

using namespace avenger::scarlet;

int main(int argc, char** argv) {
    std::shared_ptr<GlContext> context = GlContext::Make(&argc, argv);
    std::shared_ptr<NativeWindow> window = context->makeWindow();

    SkPaint paint;
    paint.reset();

    auto past = std::chrono::steady_clock::now();
    int counter = 0;
    int sampleCount = 1;
    std::chrono::microseconds averageSwapTiming(0);

    Captain captain;

    while (!window->shouldQuit()) { // Our application loop
        window->pollEvents();

        SkCanvas *canvas = window->getDrawableCanvas();
        sampleCount++;
        DrawableArea area = window->getDrawableArea();

        // create a offscreen canvas
        // this canvas can actually handle window resize events
        canvas->clear(SK_ColorLTGRAY);

        captain.setDimensions(SkRect::MakeWH(area.width, area.height));
        captain.draw(canvas);

        canvas->flush();

        // this will update the screen
        auto current = std::chrono::steady_clock::now();
        window->show();
        averageSwapTiming += std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::steady_clock::now() - current);
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - past);
        counter++;
        if (duration > std::chrono::milliseconds(1000)) {
            std::cout << counter << " Frames/sec. (Swap Buffer took "
                    << (double)averageSwapTiming.count() / sampleCount / 1000.0 << "ms (average)" << std::endl;

            // reset counters
            counter = 0;
            averageSwapTiming = std::chrono::microseconds(0);
            sampleCount = 1;


            std::printf("Drawable area: %dx%d, Canvas size: %dx%d\n",
                        area.width,
                        area.height,
                        canvas->imageInfo().width(),
                        canvas->imageInfo().height());
            past = std::chrono::steady_clock::now();
        }
    }
    return 0;
}
