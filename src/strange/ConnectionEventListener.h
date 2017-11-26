//
// Created by malcolm on 26/11/17.
//

#ifndef HELLOWORLD_CONNECTIONEVENTLISTENER_H
#define HELLOWORLD_CONNECTIONEVENTLISTENER_H

#include <shield/events/EventListener.h>

namespace avenger {
    namespace strange {

        class ConnectionEvent;

        class ConnectionEventListener : public EventListener {
        public:
            virtual void onNewConnection(std::shared_ptr<ConnectionEvent> event) = 0;

            void onEvent(std::shared_ptr<Event> event) override final;
        };

    }
}

#endif //HELLOWORLD_CONNECTIONEVENTLISTENER_H
