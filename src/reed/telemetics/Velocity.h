//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_VELOCITY_H
#define HELLOWORLD_VELOCITY_H

#include <shield/timer/Time.h>
#include <cmath>
#include "Scalar.h"
#include "Location.h"
namespace avenger {
namespace reed {

struct Velocity {
  // in points/millisecond
  Scalar vx = 0;
  Scalar vy = 0;

  Scalar direction = 0;
};

static Velocity operator/(const Displacement &displacement, Duration duration) {
  Velocity velocity{};
  velocity.vx = displacement.dx / duration.count();
  velocity.vy = displacement.dy / duration.count();

  velocity.direction = atan(velocity.vx / velocity.vy);
  return velocity;
}

static Velocity calculateVelocity(Location first, Location second, Duration duration) {
  return (second - first) / duration;
}

}
}
#endif //HELLOWORLD_VELOCITY_H
