//
// Created by malcolm on 27/11/17.
//
#include "Location.h"

namespace avenger {
namespace reed {

Displacement operator-(const Location &loc1, const Location &loc2) {
  Displacement displacement{};
  displacement.dx = loc2.x - loc1.x;
  displacement.dy = loc2.y - loc1.y;
  return displacement;
}
}
}

