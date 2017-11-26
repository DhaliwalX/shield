//
// Created by malcolm on 26/11/17.
//

#ifndef HELLOWORLD_FRAMECAPTUREEVENT_H
#define HELLOWORLD_FRAMECAPTUREEVENT_H

#include <shield/events/EventListener.h>
#include <opencv2/core/mat.hpp>
#include <memory>
#include <shield/events/Event.h>

namespace avenger {
    namespace hawkeye {

        class FrameCaptureEventListener;

        class FrameCaptureEventMetadata : public EventMetadata {
        public:
        };

        class FrameCaptureEvent : public Event {
        public:
            explicit FrameCaptureEvent(std::shared_ptr<cv::Mat> mat);

            ~FrameCaptureEvent();

            std::shared_ptr<cv::Mat> getCapturedFrame();

            EventMetadata *getMetadata() override;

            static void RegisterListener(FrameCaptureEventListener *listener);
            static void Init();
        private:
            std::shared_ptr<cv::Mat> frame_;
            static std::shared_ptr<FrameCaptureEventMetadata> metadata_;
        };
    }
}


#endif //HELLOWORLD_FRAMECAPTUREEVENT_H
