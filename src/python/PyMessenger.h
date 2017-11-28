//
// Created by malcolm on 29/11/17.
//

#ifndef SHIELD_PYMESSENGER_H
#define SHIELD_PYMESSENGER_H

#include <xavier/Messenger.h>

using namespace avenger;

class PyMessenger {
 public:
  void setConnection(std::shared_ptr<strange::TCPConnection> connection) {
    connection_ = connection;
  }

  void setMessenger(std::shared_ptr<xavier::Messenger> messenger) {
    messenger_ = messenger;
  }

  void sendMessage() {};
 private:
  std::shared_ptr<xavier::Messenger> messenger_;
  std::shared_ptr<strange::TCPConnection> connection_;

};

#endif //SHIELD_PYMESSENGER_H
