//
// Created by malcolm on 29/11/17.
//

#ifndef SHIELD_PYBOT_H
#define SHIELD_PYBOT_H

#include <shield/Bot.h>
#include <reed/telemetics/Location.h>
#include <reed/telemetics/Velocity.h>
#include <xavier/BotController.h>
#include "TelematicsMonitor.h"

namespace avenger {
namespace reed {

class PyBot {
 public:

  PyBot()  = default;

  PyBot(const PyBot &p) = default;
  PyBot &operator=(const PyBot &pytbot) = default;

  Location getCurrentLocation();
  Velocity getCurrentVelocity();

  void poll();

  void moveForward(int velocity);

  void moveBack(int velocity);

  void turnLeft(int left, int right);

  void turnRight(int left, int right);

  static PyBot Make(std::shared_ptr<Bot> bot,
                    std::shared_ptr<xavier::BotController> controller,
                    std::shared_ptr<reed::TelematicsMonitor> monitor
  );

  std::string getIP() { return bot_->ip(); }
  int id() { return bot_->getId(); }
 private:
  std::shared_ptr<Bot> bot_;
  std::shared_ptr<xavier::BotController> controller_;
  std::shared_ptr<reed::TelematicsMonitor> monitor_;
};

}
}

#endif //SHIELD_PYBOT_H
