//
// Created by malcolm on 28/11/17.
//

#include "Reed.h"

#include <boost/format.hpp>
#include <strange/ConnectionEvent.h>
#include <iostream>

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

std::vector<DetectorResult> Reed::findPollingBot(cv::Mat &mat) {
  return pollDetector_.runOn(mat);
}

void Reed::onCapture(hawkeye::FrameCaptureEvent *event) {
  auto matHandle = event->getCapturedFrame();

  if (getState() == ReedState::kDetection) {
    runDetector(*matHandle);
  } else {
    runPoller(*matHandle);
  }
}

void Reed::runDetector(cv::Mat &mat) {
  auto result = findBotsInMat(mat);

  if (result.empty()) {
    // no bots detected;
    return;
  }

  processData(result);
  cache_.update(std::move(result));
}

void Reed::runPoller(cv::Mat &mat) {
  auto results = findPollingBot(mat);

  if (results.empty()) {
    // no bots detected;
    sendPolling();
    return;
  }

  if (results.size() > 1) {
    // multiple spots detected
    return;
  }

  auto location = toLocation(results[0]);
  auto monitor = getBotMonitor(pollingBot());
  if (monitor == nullptr) {
    sendPolling();
    return;
  }

  auto lastTelematics = monitor->getLastTelematics();
  auto duration = Clock::now() - lastTelematics.timeStamp;

  if (isPossibleRangeForBot(lastTelematics.location,
                            results[0], duration.count())) {
    monitor->update(location);
  } else {
    // we will reset the old readings and restart monitoring
    monitor->restart();
    monitor->update(location);
  }

  if (poller().next()) {
    sendPolling();
  }
}

void Reed::sendPolling() {
  auto controller = getController(pollingBot());

  if (controller == nullptr) {
    if (!poller().next()) {
      enterDetectionState();
      return;
    }

    sendPolling();
  }

  controller->makeToAndFro();
}

std::shared_ptr<xavier::BotController> Reed::getController(std::shared_ptr<Bot> bot) {
  auto contrIt = std::find_if(controllers_.begin(),
                              controllers_.end(),
                              [&bot]
                                  (const std::shared_ptr<xavier::BotController> &controller) {
    return bot == controller->bot();
  });

  if (contrIt == controllers_.end()) {
    return nullptr;
  }

  return *contrIt;
}

void Reed::startService() {
  std::cout << "Starting TCP server at 3000" << std::endl;
  hawkeye::FrameCaptureEvent::RegisterListener(this);
  strange::ConnectionEvent::Subscribe(this);

  server_.startListening();
}

BotContainer &Reed::getConnectedBots() {
  return registry_.getConnectedBots();
}

void Reed::processData(std::vector<DetectorResult> &result) {
  auto &bots = getConnectedBots();

  // find all the bots who have moved
  for (auto &bot : bots) {
    auto monitor = getBotMonitor(bot);

    if (!monitor) {
      fprintf(stderr, "No monitor available for %d[%s]",
              bot->getId(),
              bot->ip().c_str());

      // now we have bot which is visible but don't know ip of same
      enterPollState();
      // now in next frame we will poll the bots
      sendPolling();
      break;
    }

    auto lastTelematics = monitor->getLastTelematics();
    // duration between last and this update
    auto duration = std::chrono::duration_cast<Milliseconds>(
        Clock::now() - lastTelematics.timeStamp);
    for (auto &location : result) {
      if (isPossibleRangeForBot(lastTelematics.location,
                                location, duration.count())) {
        monitor->update(toLocation(location));
      } else {
        std::cerr << "Warning: " << monitor->bot() << " has moved much farther." << std::endl;
        //monitor->update(toLocation(location));
        continue;
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

  // attach a controller to the bot
  auto controller = xavier::BotController::Make(bot);
  controllers_.push_back(controller);

  // attach a monitor to the bot
  monitors_.push_back(TelematicsMonitor::Make(bot));
}

void Reed::onNewConnection(std::shared_ptr<strange::ConnectionEvent> event) {
  std::cout << "New bot connected: " << event->getConnection()->getIP() << std::endl;
  std::shared_ptr<Bot> bot = Bot::Create(event->getConnection());
  registerBot(bot);
}

}
}
