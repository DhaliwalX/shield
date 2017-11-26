//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_LOCATION_H
#define HELLOWORLD_LOCATION_H

#include "Scalar.h"
namespace avenger {
namespace reed {

struct Location {
  Scalar x = 0;
  Scalar y = 0;
};

struct Displacement {
  Scalar dx = 0;
  Scalar dy = 0;
};

Displacement operator-(const Location &loc1, const Location &loc2);

}
}

#endif //HELLOWORLD_LOCATION_H
