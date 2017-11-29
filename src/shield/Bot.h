//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_BOT_H
#define HELLOWORLD_BOT_H

#include <string>
#include <memory>
#include <strange/TCPConnection.h>

namespace avenger {

enum class BotState {
  kResting,
  kToAndFro,
  kForward,
  kBackward,
  kTurningLeft,
  kTurningRight,
};

class Bot {
  Bot(int id, std::shared_ptr<strange::TCPConnection> connection);

  static int botNumber;
 public:

  static std::shared_ptr<Bot> Create(std::shared_ptr<strange::TCPConnection> connection);

  int getId() { return id_; }

  bool isConnected() { return connected_; }
  void setConnected(bool connected) { connected_ = connected; }
  void setVisible(bool visible) { visible_ = visible; }
  bool isVisible() { return visible_; }

  std::string ip() const { return connection_->getIP(); }

  auto connection() { return connection_; }

 private:
  int id_;
  bool connected_;
  bool visible_;
  std::shared_ptr<strange::TCPConnection> connection_;
};


std::ostream &operator<<(std::ostream &os, std::shared_ptr<Bot> bot);

}
#endif //HELLOWORLD_BOT_H
