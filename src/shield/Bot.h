//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_BOT_H
#define HELLOWORLD_BOT_H

#include <string>
#include <memory>

namespace avenger {

class Bot {
  Bot(int id, const std::string &ip);

  static int botNumber;
 public:

  static std::shared_ptr<Bot> Create(const std::string &ip);

  int getId() { return id_; }

  bool isConnected() { return connected_; }
  void setConnected(bool connected) { connected_ = connected; }
  void setVisible(bool visible) { visible_ = visible; }
  bool isVisible() { return visible_; }

  const std::string &ip() const { return ip_; }
 private:
  int id_;
  bool connected_;
  bool visible_;
  std::string ip_;
};

}
#endif //HELLOWORLD_BOT_H
