//
// Created by malcolm on 25/11/17.
//

#include <opencv2/videoio/videoio_c.h>
#include <shield/events/dispatcher.h>
#include <thread>
#include <iostream>
#include <opencv/cv.hpp>
#include <chrono>
#include "Camera.h"
#include "shield/timer/Time.h"

namespace avenger {
namespace hawkeye {

std::shared_ptr<Camera> Camera::camera_;

Camera::Camera(const FrameDescriptor& descriptor)
    : descriptor_{descriptor}, capture{} {}

Camera* Camera::GetInstance() {
  const FrameDescriptor frameDescriptor(SHIELD::kSHIELDCameraWidth,
                                        SHIELD::kSHIELDCameraHeight, 30);
  if (!camera_) {
    camera_ = std::make_unique<Camera>(frameDescriptor);
  }
  return camera_.get();
}

bool Camera::TryInstall(int cameraNumber) {
  FrameCaptureEvent::Init();
  GetInstance()->openCamera(cameraNumber);
}

void Camera::addListener(FrameCaptureEventListener* listener) {
  FrameCaptureEvent::RegisterListener(listener);
}

bool Camera::openCamera(int cameraNumber) {
  capture = std::make_unique<cv::VideoCapture>(0);

  if (!capture->isOpened()) {
    return false;
  }

  capture->set(CV_CAP_PROP_FRAME_HEIGHT, descriptor_.height_);
  capture->set(CV_CAP_PROP_FRAME_WIDTH, descriptor_.width_);
  capture->set(CV_CAP_PROP_FPS, 60);
  return capture->isOpened();
}

Camera::~Camera() {
  if (capture && capture->isOpened()) {
    capture->release();
  }
}

void Camera::startCaptureThread() {
  captureThread_ = std::make_unique<std::thread>([this]() { captureLoop(); });
}

void Camera::captureLoop() {
  while (true) {
    std::shared_ptr<cv::Mat> frame = std::make_shared<cv::Mat>();

    *capture >> (*frame);

    if (frame->empty())
      continue;

    // create a FrameCaptureEvent and dispatch it
    auto event = std::make_shared<FrameCaptureEvent>(frame);

    imshow("Live", *frame);
    if (cv::waitKey(5) > 0) {
      break;
    };
    dispatch(SHIELD::GetInstance(), event);
  }
}

void Camera::StartCapturing() {
  GetInstance()->startCaptureThread();
}

void Camera::AddListener(FrameCaptureEventListener* listener) {
  GetInstance()->addListener(listener);
}
}
}
