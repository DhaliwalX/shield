#ifndef HELLOWORLD_EVENT_H
#define HELLOWORLD_EVENT_H

#include <memory>
#include <string>
#include <vector>

#include "EventListener.h"

namespace avenger {

    class EventMetadata {
    public:
        EventMetadata() : listeners_(0, nullptr) { }
        virtual ~EventMetadata() = default;

        void registerListener(EventListener *listener);

        virtual void notifyListeners(std::shared_ptr<Event> event);
    protected:
        std::vector<EventListener*> listeners_;
    };

    class Event {
        static uint32_t currentInstanceId_;
    public:
        Event();

        virtual ~Event() = default;

        virtual EventMetadata *getMetadata() = 0;
        uint32_t getId();

        static void Notify(std::shared_ptr<Event> event);
    private:
        uint32_t id_;
    };

}

#endif //HELLOWORLD_EVENT_H
