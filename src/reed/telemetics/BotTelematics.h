//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_BOTTELEMETICS_H
#define HELLOWORLD_BOTTELEMETICS_H

#include "Velocity.h"
namespace avenger {
namespace reed {

struct BotTelematics {
  Velocity velocity{};
  Location location{};
  TimePointMs timeStamp{};

  BotTelematics() = default;
  BotTelematics(const BotTelematics &other) = default;
};

}
}

#endif //HELLOWORLD_BOTTELEMETICS_H
