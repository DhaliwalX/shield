//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_BOTPARAMETERS_H
#define HELLOWORLD_BOTPARAMETERS_H
#include <cstdint>
namespace avenger {
namespace xavier {

// this is the common class which will be shared between both arduino
// code and controller code
//
// This acts as a format of data transfered between arduino and server

enum BotCommand {
  kNoop,
  kMoveF,
  kMoveB,
  kMoveL,
  kMoveR,
  kStop,
  kPoll
};

struct BotParameters {
  uint8_t command_ = kNoop;
  uint8_t leftMotorsSpeed = 0;
  uint8_t rightMotorsSpeed = 0;

  static BotParameters MakePoll() {
    BotParameters parameters;
    parameters.command_ = kPoll;
    parameters.leftMotorsSpeed = 0;
    parameters.rightMotorsSpeed = 0;
    return parameters;
  }

  static BotParameters Make(uint8_t command, uint8_t left, uint8_t right, uint8_t degrees = 0) {
    BotParameters parameters;
    parameters.command_ = command;
    parameters.leftMotorsSpeed = left;
    parameters.rightMotorsSpeed = right;
    return parameters;
  }

  static BotParameters MakeF(uint8_t speed) {
    return Make(kMoveF, speed, speed);
  }

  static BotParameters MakeB(uint8_t speed) {
    return Make(kMoveB, speed, speed);
  }

  static BotParameters MakeL(uint8_t l, uint8_t r) {
    return Make(kMoveL, l, r);
  }

  static BotParameters MakeR(uint8_t l, uint8_t r) {
    return Make(kMoveR, l, r);
  }
};

}
}

#endif //HELLOWORLD_BOTPARAMETERS_H
