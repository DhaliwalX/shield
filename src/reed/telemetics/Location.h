//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_LOCATION_H
#define HELLOWORLD_LOCATION_H

#include <SkPoint.h>
#include "Scalar.h"
namespace avenger {
namespace reed {

struct Point {
  Scalar x = 0;
  Scalar y = 0;

  Point() = default;
  Point(const Scalar &fx, const Scalar &fy)
      : x{ fx }, y{ fy }
  { }

  Point(const Point &) = default;
  Point &operator=(const Point &p) = default;
};

struct Location {
  Scalar x = 0;
  Scalar y = 0;
  Scalar r = 0;
};

struct Displacement {
  Scalar dx = 0;
  Scalar dy = 0;
};

Displacement operator-(const Location &loc1, const Location &loc2);

}
}

#endif //HELLOWORLD_LOCATION_H
