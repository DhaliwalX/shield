//
// Created by malcolm on 28/11/17.
//

#ifndef SHIELD_MESSENGER_H
#define SHIELD_MESSENGER_H

#include <strange/TCPConnection.h>
#include "BotParameters.h"

#include <set>

namespace avenger {
namespace xavier {

using MessageCache = std::set<strange::MessageHandle>;

class Messenger : public strange::TCPWriteListener {
 public:
  void sendMessage(std::shared_ptr<strange::TCPConnection> connection,
                   const BotParameters &parameters) {
    char *message = new char[sizeof(BotParameters)];

    strange::MessageHandle handle(message);
    memcpy(message, &parameters, sizeof(parameters));
    cache_.insert(handle);

    connection->sendMessage(handle, this);
  }

  void onComplete(const strange::MessageHandle &handle) override {
    cache_.erase(handle);
  }

 private:
  // as our services are asynchronous therefore cache is required
  // to keep the message alive until write is completed.
  MessageCache cache_;
};

}
}

#endif //SHIELD_MESSENGER_H
