//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_TIME_H
#define HELLOWORLD_TIME_H

#include <chrono>
namespace avenger {

using Milliseconds = std::chrono::milliseconds;
using Microseconds = std::chrono::microseconds;

using Duration = std::chrono::duration<double>;

using Clock = std::chrono::steady_clock;

using TimePointMs = std::chrono::time_point<Clock>;
using TimePointUs = std::chrono::time_point<Clock>;

}

#endif //HELLOWORLD_TIME_H
