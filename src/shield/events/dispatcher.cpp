//
// Created by malcolm on 26/11/17.
//

#include <cassert>
#include <utility>
#include "dispatcher.h"

namespace avenger {
    void dispatch(avenger::SHIELD *shield, std::shared_ptr<avenger::Event> event) {
        assert(shield && "SHIELD was null during dispatching event.");
        shield->postEvent(std::move(event));
    }
}
