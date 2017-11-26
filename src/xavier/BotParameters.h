//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_BOTPARAMETERS_H
#define HELLOWORLD_BOTPARAMETERS_H
#include <cstdint>
namespace avenger {
namespace xavier {

// this is the common class which will be shared between both arduino
// code and controller code
//
// This acts as a format of data transfered between arduino and server
struct BotParameters {
  uint8_t leftMotorsSpeed;
  uint8_t rightMotorsSpeed;
};

}
}

#endif //HELLOWORLD_BOTPARAMETERS_H
