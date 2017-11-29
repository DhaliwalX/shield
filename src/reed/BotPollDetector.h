//
// Created by malcolm on 28/11/17.
//

#ifndef SHIELD_BOTPOLLDETECTOR_H
#define SHIELD_BOTPOLLDETECTOR_H

#include <opencv2/core/mat.hpp>
#include "BotDetector.h"

namespace avenger {
namespace reed {

class BotPollDetector {
 public:
  std::vector<DetectorResult> runOn(cv::Mat &mat);
};

}
}

#endif //SHIELD_BOTPOLLDETECTOR_H
