//
// Created by malcolm on 29/11/17.
//

#include "PyBot.h"

namespace avenger {
namespace reed {

Location PyBot::getCurrentLocation() {
  return monitor_->getLastTelematics().location;
}

Velocity PyBot::getCurrentVelocity() {
  return monitor_->getLastTelematics().velocity;
}

void PyBot::poll() {
  controller_->makeToAndFro();
}

void PyBot::moveForward(int velocity) {
  controller_->moveForward(velocity);
}

void PyBot::moveBack(int velocity) {
  controller_->moveBackward(velocity);
}

void PyBot::turnLeft(int left, int right) {
  controller_->turnLeft(left, right);
}

void PyBot::turnRight(int left, int right) {
  controller_->turnRight(left, right);
}

PyBot PyBot::Make(std::shared_ptr<Bot> bot,
                  std::shared_ptr<xavier::BotController> controller,
                  std::shared_ptr<reed::TelematicsMonitor> monitor) {
  PyBot pyBot;
  pyBot.bot_ = bot;
  pyBot.controller_ = controller;
  pyBot.monitor_ = monitor;
  return pyBot;
}
}
}
