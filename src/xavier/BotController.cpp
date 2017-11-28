//
// Created by malcolm on 27/11/17.
//

#include "BotController.h"

namespace avenger {
namespace xavier {

void BotController::makeToAndFro() {
  messenger.sendMessage(connection_, BotParameters::MakePoll());
}

void BotController::moveForward(uint8_t speed) {
  messenger.sendMessage(connection_, BotParameters::MakeF(speed));
}

void BotController::moveBackward(uint8_t speed) {
  messenger.sendMessage(connection_, BotParameters::MakeB(speed));
}

void BotController::turnLeft(uint8_t l, uint8_t r) {
  messenger.sendMessage(connection_, BotParameters::MakeL(l, r));
}

void BotController::turnRight(uint8_t l, uint8_t r) {
  messenger.sendMessage(connection_, BotParameters::MakeR(l, r));
}

}
}
