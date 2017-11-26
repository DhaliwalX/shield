//
// Created by malcolm on 26/11/17.
//

#ifndef HELLOWORLD_DISPATCHER_H
#define HELLOWORLD_DISPATCHER_H

#include <shield/SHIELD.h>
#include "Event.h"

namespace avenger {
// dispatch the event which will notify all the listeners
// Did you notice?
//    ...only those having shield context are allowed to dispatch ;-)
void dispatch(SHIELD* shield, std::shared_ptr<Event> event);
}

#endif  // HELLOWORLD_DISPATCHER_H
