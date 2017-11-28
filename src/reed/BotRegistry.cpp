//
// Created by malcolm on 28/11/17.
//

#include <algorithm>
#include "BotRegistry.h"

namespace avenger {
namespace reed {

BotRegistry::BotRegistry() = default;

void BotRegistry::registerBot(std::shared_ptr<Bot> bot) {
  botList_.emplace_back(std::move(bot));
}

void BotRegistry::unregisterBot(std::shared_ptr<Bot> bot) {
  std::remove_if(botList_.begin(), botList_.end(),
                 [&bot](const auto &other){ return bot == other; });
}

size_t BotRegistry::numConnected() {
  return botList_.size();
}

std::shared_ptr<Bot> BotRegistry::findBotByIP(const std::string &ip) {
  return *std::find_if(botList_.begin(), botList_.end(),
              [&ip](const auto &other){ return other->ip() == ip; });
}

BotContainer &BotRegistry::getConnectedBots() {
  return botList_;
}

}
}
