//
// Created by malcolm on 28/11/17.
//

#ifndef SHIELD_BOTREGISTRY_H
#define SHIELD_BOTREGISTRY_H

#include <shield/Bot.h>
#include <vector>
namespace avenger {
namespace reed {

using BotContainer = std::vector<std::shared_ptr<Bot>>;

// BotRegistry contains the information about the registered
// bot. (kind of acts like database of bots)
class BotRegistry {
 public:
  BotRegistry();

  void registerBot(std::shared_ptr<Bot> bot);

  void unregisterBot(std::shared_ptr<Bot> bot);

  size_t numConnected();

  std::shared_ptr<Bot> findBotByIP(const std::string &ip);

  BotContainer &getConnectedBots();
 private:
  BotContainer botList_;
};

}
}

#endif //SHIELD_BOTREGISTRY_H
