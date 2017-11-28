//
// Created by malcolm on 27/11/17.
//

#ifndef SHIELD_BOTDETECTOR_H
#define SHIELD_BOTDETECTOR_H

#include <vector>
#include <reed/telemetics/Scalar.h>
#include <reed/telemetics/Location.h>
#include <opencv2/core/mat.hpp>
#include <memory>

namespace avenger {
namespace reed {

struct DetectorResult {
  Point center_;
  Scalar radius_;

  DetectorResult(const Point &center, const Scalar &radius)
      : center_{ center }, radius_{ radius }
  { }
};

class BotDetector {
 public:
  std::vector<DetectorResult> runOn(cv::Mat &mat);
};

}
}

#endif //SHIELD_BOTDETECTOR_H
