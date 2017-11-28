//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_BOTCONTROLLER_H
#define HELLOWORLD_BOTCONTROLLER_H

#include <strange/TCPConnection.h>
#include <shield/Bot.h>
#include <reed/telemetics/Scalar.h>
#include <reed/telemetics/Location.h>
#include "Messenger.h"

namespace avenger {
namespace xavier {

// main class to control a single bot
// it provides following operations
class BotController {
 public:
  BotController();

  // moves bot to and fro, this motion will be detected by reed
  // and if there was polling going on and this bot comes under
  // viewport, bot will be set visible and now we have control
  // over it.
  void makeToAndFro();

  void moveForward(uint8_t speed);

  void moveBackward(uint8_t speed);

  void turnLeft(uint8_t l, uint8_t r);

  void turnRight(uint8_t l, uint8_t r);

  void setBot(std::shared_ptr<Bot> bot) {
    bot_ = std::move(bot);
  }

  void setConnection(std::shared_ptr<strange::TCPConnection> connection) {
    connection_ = std::move(connection);
  }

 private:
  std::shared_ptr<Bot> bot_;
  Messenger messenger;
  std::shared_ptr<strange::TCPConnection> connection_;
};

}
}

#endif //HELLOWORLD_BOTCONTROLLER_H
