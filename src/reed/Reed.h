//
// Created by malcolm on 28/11/17.
//

#ifndef SHIELD_REED_H
#define SHIELD_REED_H

#include <hawkeye/FrameCaptureEventListener.h>
#include <shield/IOService.h>
#include <strange/Server.h>
#include <strange/ConnectionEventListener.h>
#include <xavier/BotController.h>
#include "BotRegistry.h"
#include "BotDetector.h"
#include "TelematicsMonitor.h"
#include "BotPollDetector.h"
#include "PyBot.h"

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

class Poller {
 public:
  explicit Poller(BotContainer &container)
      : parent_{ container }
  {}

  void setBot(BotContainer::iterator bot) { bot_ = bot; }
  std::shared_ptr<Bot> &bot() { return *bot_; }

  bool next() {
    bool shouldMove = !(bot_+1 == parent_.end());

    if (shouldMove)
      bot_++;

    return shouldMove;
  }

  void start() {
    bot_ = parent_.begin();
  }
 private:
  BotContainer::iterator bot_;
  BotContainer &parent_;
};

enum class ReedState {
  kDetection,
  kPoll
};

class Reed : public hawkeye::FrameCaptureEventListener,
             public strange::ConnectionEventListener {
 public:
  Reed()
      : state_{ReedState::kDetection},
        service_{},
        server_(service_, 3000),
        registry_{},
        poller_{registry_.getConnectedBots()}
  { }

  void runPoller(cv::Mat &mat);
  void runDetector(cv::Mat &mat);
  std::vector<DetectorResult> findBotsInMat(cv::Mat &mat);
  std::vector<DetectorResult> findPollingBot(cv::Mat &mat);

  auto &result() { return cache_.get(); }

  void startService();

  BotContainer &getConnectedBots();

  std::shared_ptr<TelematicsMonitor> getBotMonitor(std::shared_ptr<Bot> &bot);

  void processData(std::vector<DetectorResult> &result);

  void registerBot(std::shared_ptr<Bot> bot);

  void enterPollState() {
    state_ = ReedState::kPoll;
    if (getConnectedBots().empty()) {
      return;
    }

    poller().start();
  }

  void enterDetectionState() { state_ = ReedState::kDetection; }

  ReedState getState() { return state_; }

  // listener's callbacks
  void onCapture(hawkeye::FrameCaptureEvent *event) override;
  void onNewConnection(std::shared_ptr<strange::ConnectionEvent> event) override;

  auto &pollingBot() { return poller_.bot(); }
  Poller &poller() { return poller_; }

  auto getPythonControllers() { return toPythonList(controllers_, monitors_); }
 private:
  ReedState state_;

  // server
  strange::IOService service_;
  strange::Server server_;

  // bots currently connected
  BotRegistry registry_;

  // detectors
  BotDetector detector_;
  BotPollDetector pollDetector_;

  // detector's helper;
  DetectorResultCache cache_;

  std::vector<std::shared_ptr<TelematicsMonitor>> monitors_;
  std::vector<std::shared_ptr<xavier::BotController>> controllers_;

  // bot currently being polled
  Poller poller_;

  bool isPossibleRangeForBot(Location location, DetectorResult &result, int64_t duration);
  Location toLocation(DetectorResult &result);
  void sendPolling();
  std::shared_ptr<xavier::BotController> getController(std::shared_ptr<Bot> bot);

  std::vector<PyBot> toPythonList(
      std::vector<std::shared_ptr<xavier::BotController>> &list,
      std::vector<std::shared_ptr<reed::TelematicsMonitor>> &monitor
  ) {
    std::vector<PyBot> pyBots;
    for (auto &controller : list) {
      auto monitor = getBotMonitor(controller->bot());

      if (monitor == nullptr) {
        continue;
      }

      pyBots.emplace_back(PyBot::Make(controller->bot(), controller, monitor));
    }

    return pyBots;
  }

};

class HandleReed {
 public:
  HandleReed() : reed_{ std::make_shared<Reed>() } {}
  HandleReed(const HandleReed &other) = default;
  HandleReed &operator=(const HandleReed &other) = default;

  auto getPythonControllers() {
    return reed_->getPythonControllers();
  }

  void startService() { reed_->startService(); }

  auto &reed() { return reed_; }
 private:
  std::shared_ptr<Reed> reed_;
};

}
}

#endif //SHIELD_REED_H
