//
// Created by malcolm on 28/11/17.
//

#include "Reed.h"

namespace avenger {
namespace reed {

bool Reed::isPossibleRangeForBot(Location location,
                                 DetectorResult &result,
                                 int64_t duration) {
  static const Scalar kThresholdDistance = 50;

  Displacement displacement = toLocation(result) - location;
  Scalar distance = sqrt(displacement.dx * displacement.dx
                             + displacement.dy * displacement.dy);

  return distance < kThresholdDistance;
}

Location Reed::toLocation(DetectorResult &result) {
  Location location;
  location.x = result.center_.x;
  location.y = result.center_.y;
  location.r = result.radius_;
  return location;
}

std::vector<DetectorResult> Reed::findBotsInMat(cv::Mat &mat) {
  return detector_.runOn(mat);
}

void Reed::onCapture(hawkeye::FrameCaptureEvent *event) {
  auto matHandle = event->getCapturedFrame();
  auto result = findBotsInMat(*matHandle);

  if (result.empty()) {
    // no bots detected;
    return;
  }

  processData(result);
  cache_.update(std::move(result));
}

void Reed::startService() {
  hawkeye::FrameCaptureEvent::RegisterListener(this);
}

BotContainer &Reed::getConnectedBots() {
  return registry_.getConnectedBots();
}

void Reed::processData(std::vector<DetectorResult> &result) {
  auto &bots = getConnectedBots();

  // find all the bots who have moved
  for (auto &bot : bots) {
    auto monitor = getBotMonitor(bot);

    auto lastTelematics = monitor->getLastTelematics();
    // duration between last and this update
    auto duration = std::chrono::duration_cast<Milliseconds>(
        Clock::now() - lastTelematics.timeStamp);
    for (auto &location : result) {
      if (isPossibleRangeForBot(lastTelematics.location,
                                location, duration.count())) {
        monitor->update(toLocation(location));
      } else {
        // TODO: write code here
      }
    }
  }
}

std::shared_ptr<TelematicsMonitor> Reed::getBotMonitor(std::shared_ptr<Bot> &bot) {
  auto mayBe = std::find_if(monitors_.begin(), monitors_.end(),
                       [&bot](const auto &b) { return b->bot() == bot; }
  );

  if (mayBe == std::end(monitors_)) {
    return nullptr;
  }

  return *mayBe;
}

void Reed::registerBot(std::shared_ptr<Bot> bot) {
  registry_.registerBot(bot);

  // attach a monitor to the bot
  monitors_.push_back(TelematicsMonitor::Make(bot));
}

}
}
