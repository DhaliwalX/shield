//
// Created by malcolm on 27/11/17.
//

#include "Bot.h"

namespace avenger {

int Bot::botNumber = 0;

std::shared_ptr<Bot> Bot::Create(const std::string &ip) {
  return std::shared_ptr<Bot>(new Bot(botNumber++, ip));
}

Bot::Bot(int id, const std::string &ip)
  : id_{ id }, ip_{ ip }, connected_{ false }, visible_{ false }
{}

}