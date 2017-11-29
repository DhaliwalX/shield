//
// Created by malcolm on 27/11/17.
//

#include "Bot.h"

namespace avenger {

int Bot::botNumber = 0;

std::shared_ptr<Bot> Bot::Create(std::shared_ptr<strange::TCPConnection> connection) {
  return std::shared_ptr<Bot>(new Bot(botNumber++, connection));
}

Bot::Bot(int id, std::shared_ptr<strange::TCPConnection> connection)
  : id_{ id }, connection_{ connection }, connected_{ false }, visible_{ false }
{}

std::ostream &operator<<(std::ostream &os, std::shared_ptr<Bot> bot) {
  os << "Bot{id=" << bot->getId() << ", ip=" << bot->ip() << "}";
  return os;
}
}