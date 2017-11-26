//
// Created by malcolm on 26/11/17.
//

#include "FrameCaptureEvent.h"

#include <utility>
#include <iostream>
#include "FrameCaptureEventListener.h"

namespace avenger {
namespace hawkeye {

std::shared_ptr<FrameCaptureEventMetadata> FrameCaptureEvent::metadata_;

FrameCaptureEvent::FrameCaptureEvent(std::shared_ptr<cv::Mat> mat)
    : frame_{std::move(mat)} {}

std::shared_ptr<cv::Mat> FrameCaptureEvent::getCapturedFrame() {
  return frame_;
}

void FrameCaptureEvent::RegisterListener(FrameCaptureEventListener* listener) {
  metadata_->registerListener(listener);
}

EventMetadata* FrameCaptureEvent::getMetadata() {
  return metadata_.get();
}

void FrameCaptureEvent::Init() {
  metadata_ = std::make_shared<FrameCaptureEventMetadata>();
}

FrameCaptureEvent::~FrameCaptureEvent() = default;
}
}