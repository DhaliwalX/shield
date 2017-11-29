//
// Created by malcolm on 27/11/17.
//

#include "BotController.h"

namespace avenger {
namespace xavier {

void BotController::makeToAndFro() {
  messenger->queueMessage(BotParameters::MakePoll());
}

void BotController::moveForward(uint8_t speed) {
  messenger->queueMessage(BotParameters::MakeF(speed));
}

void BotController::moveBackward(uint8_t speed) {
  messenger->queueMessage(BotParameters::MakeB(speed));
}

void BotController::turnLeft(uint8_t l, uint8_t r) {
  messenger->queueMessage(BotParameters::MakeL(l, r));
}

void BotController::turnRight(uint8_t l, uint8_t r) {
  messenger->queueMessage(BotParameters::MakeR(l, r));
}

BotController::BotController() = default;

std::shared_ptr<BotController>
BotController::Make(std::shared_ptr<Bot> bot) {
  auto controller = std::make_shared<BotController>();
  controller->setConnection(bot->connection());
  controller->setBot(bot);
  controller->messenger = Messenger::Make(bot->connection());
  controller->messenger->startThread();
  return controller;
}

}
}
