//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_BOTCONTROLLER_H
#define HELLOWORLD_BOTCONTROLLER_H

#include <strange/TCPConnection.h>
namespace avenger {
namespace xavier {

// main class to control a single bot
// it provides following operations
class BotController {
 public:
  BotController();



 private:
  // unique id of this bot
  int id_;

  std::shared_ptr<strange::TCPConnection> connection_;
};

}
}

#endif //HELLOWORLD_BOTCONTROLLER_H
