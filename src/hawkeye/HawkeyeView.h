//
// Created by malcolm on 26/11/17.
//

#ifndef HELLOWORLD_HAWKEYEVIEW_H
#define HELLOWORLD_HAWKEYEVIEW_H

#include <scarlet/View.h>
#include <opencv2/core/mat.hpp>
#include <SkBitmap.h>
#include <mutex>

#include "spidey/MatToBitmapConvertor.h"
#include "FrameCaptureEventListener.h"

namespace avenger {
namespace hawkeye {

class HawkeyeView : public scarlet::View, public FrameCaptureEventListener {
 public:
  HawkeyeView();

  void onCreate(SkCanvas* canvas) override;

  void onCapture(FrameCaptureEvent* event) override;

 private:
  std::shared_ptr<cv::Mat> currentFrame_;
  SkBitmap store_;
  BitmapRef bitmapCache_;

  std::mutex lock_;
};
}
}

#endif  // HELLOWORLD_HAWKEYEVIEW_H
