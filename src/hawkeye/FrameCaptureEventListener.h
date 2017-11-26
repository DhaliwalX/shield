//
// Created by malcolm on 26/11/17.
//

#ifndef HELLOWORLD_FRAMECAPTUREEVENTLISTENER_H
#define HELLOWORLD_FRAMECAPTUREEVENTLISTENER_H

#include "FrameCaptureEvent.h"

namespace avenger {
    namespace hawkeye {
        class FrameCaptureEventListener : public EventListener {
        public:
            virtual void onCapture(FrameCaptureEvent *event) = 0;

            void onEvent(std::shared_ptr<Event> event) override;
        };
    }
}


#endif //HELLOWORLD_FRAMECAPTUREEVENTLISTENER_H
