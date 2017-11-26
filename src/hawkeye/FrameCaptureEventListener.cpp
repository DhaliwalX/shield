//
// Created by malcolm on 26/11/17.
//

#include "FrameCaptureEventListener.h"

namespace avenger {
    namespace hawkeye {
        void FrameCaptureEventListener::onEvent(std::shared_ptr<Event> event) {
            onCapture((FrameCaptureEvent*)event.get());
        }
    }
}