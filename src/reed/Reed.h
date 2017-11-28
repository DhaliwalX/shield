//
// Created by malcolm on 28/11/17.
//

#ifndef SHIELD_REED_H
#define SHIELD_REED_H

#include <hawkeye/FrameCaptureEventListener.h>
#include "BotRegistry.h"
#include "BotDetector.h"
#include "TelematicsMonitor.h"

namespace avenger {
namespace reed {

class DetectorResultCache {
 public:
  DetectorResultCache() = default;

  void update(std::vector<DetectorResult> &&result) {
    cache_ = result;
  }

  auto &get() { return cache_; }
 private:
  std::vector<DetectorResult> cache_;
};

class Reed : public hawkeye::FrameCaptureEventListener {
 public:
  Reed() = default;

  void onCapture(hawkeye::FrameCaptureEvent *event) override;

  std::vector<DetectorResult> findBotsInMat(cv::Mat &mat);

  auto &result() { return cache_.get(); }

  void startService();

  BotContainer &getConnectedBots();

  std::shared_ptr<TelematicsMonitor> getBotMonitor(std::shared_ptr<Bot> &bot);

  void processData(std::vector<DetectorResult> &result);

  void registerBot(std::shared_ptr<Bot> bot);
 private:
  BotRegistry registry_;
  BotDetector detector_;
  DetectorResultCache cache_;
  std::vector<std::shared_ptr<TelematicsMonitor>> monitors_;

  bool isPossibleRangeForBot(Location location, DetectorResult &result, int64_t duration);
  Location toLocation(DetectorResult &result);
};

}
}

#endif //SHIELD_REED_H
