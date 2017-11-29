//
// Created by malcolm on 28/11/17.
//

#ifndef SHIELD_MESSENGER_H
#define SHIELD_MESSENGER_H

#include <strange/TCPConnection.h>
#include "BotParameters.h"

#include <set>
#include <queue>
#include <thread>
#include <iostream>

namespace avenger {
namespace xavier {

using MessageCache = std::set<char*>;

class Messenger : public strange::TCPWriteListener {
 public:
  static int counter_;
  static std::shared_ptr<Messenger> Make(std::shared_ptr<strange::TCPConnection> conn);

  void sendMessage(const BotParameters &parameters) {
    char *message = new char[3];
    message[0] = parameters.command_;
    message[1] = parameters.leftMotorsSpeed;
    message[2] = parameters.rightMotorsSpeed;

    cache_.insert(message);
    connection->sendMessage(message, this);
  }

  void onComplete(char *handle) override {
    static int counter = 0;
    cache_.erase(handle);
    delete []handle;
    std::cout << counter++ << ": Successfully sent message " << std::endl;
  }

  void send() {
    if (shouldStop) {
      return;
    }
    if (messageQueue_.empty()) {
      sendMessage(BotParameters::Make(BotCommand::kNoop, 0, 0));
    }
    sendMessage(messageQueue_.front());
    messageQueue_.pop();
  }

  void startThread() {
    thread_ = std::make_unique<std::thread>([this]{
      for (;;) {

        if (shouldStop) {
          break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        send();
      }
    });
  }

  void stop() {
    shouldStop = true;
  }

  void queueMessage(const BotParameters &p) {
    messageQueue_.push(p);
  }

 private:
  // as our services are asynchronous therefore cache is required
  // to keep the message alive until write is completed.
  MessageCache cache_;
  bool shouldStop = true;
  std::unique_ptr<std::thread> thread_;

  std::queue<BotParameters> messageQueue_;

  std::shared_ptr<strange::TCPConnection> connection;
  static std::shared_ptr<Messenger> messenger_;
};

}
}

#endif //SHIELD_MESSENGER_H
