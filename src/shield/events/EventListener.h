//
// Created by malcolm on 25/11/17.
//

#ifndef HELLOWORLD_EVENTSUBSCRIBER_H
#define HELLOWORLD_EVENTSUBSCRIBER_H

#include <memory>

namespace avenger {
    class Event;

    class EventListener {
    public:
        virtual ~EventListener() = default;

        virtual void onEvent(std::shared_ptr<Event> event) = 0;
    };
}

#endif //HELLOWORLD_EVENTSUBSCRIBER_H
