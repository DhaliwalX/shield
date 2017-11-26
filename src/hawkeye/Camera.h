//
// Created by malcolm on 25/11/17.
//

#ifndef HELLOWORLD_CAMERA_H
#define HELLOWORLD_CAMERA_H

#include "shield/events/Event.h"
#include "FrameCaptureEventListener.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>

#include <thread>

namespace avenger {
namespace hawkeye {

struct FrameDescriptor {
  int width_;
  int height_;
  int framerate_;

  FrameDescriptor() : width_{0}, height_{0}, framerate_{0} {}

  FrameDescriptor(const FrameDescriptor& other)
      : width_{other.width_},
        height_{other.height_},
        framerate_{other.framerate_} {}

  FrameDescriptor(int width, int height, int framerate)
      : width_{width}, height_{height}, framerate_{framerate} {}
};

class Camera {
 public:
  Camera(const FrameDescriptor& descriptor);

  ~Camera();

  static Camera* GetInstance();

  // try to install `cameraNumber`th camera
  static bool TryInstall(int cameraNumber = 0);
  static void StartCapturing();
  static void AddListener(FrameCaptureEventListener* listener);

  void addListener(FrameCaptureEventListener* listener);

  void captureLoop();

  void startCaptureThread();

 private:
  bool openCamera(int cameraNumber);

  FrameDescriptor descriptor_;
  std::unique_ptr<cv::VideoCapture> capture;
  std::unique_ptr<std::thread> captureThread_;

  static std::shared_ptr<Camera> camera_;
};
}
}

#endif  // HELLOWORLD_CAMERA_H
