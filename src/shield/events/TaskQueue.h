//
// Created by malcolm on 25/11/17.
//

#ifndef HELLOWORLD_EVENTQUEUE_H
#define HELLOWORLD_EVENTQUEUE_H

#include <list>
#include <memory>
#include <utility>
#include "Event.h"

namespace avenger {
    class Task {
    public:
        Task(std::shared_ptr<Event> event, std::function<void(std::shared_ptr<Event>)> function)
                : event_{std::move(event)},
                  handler_{std::move(function)}
        { }

        Task(const Task &other) = default;

        void execute() {
            handler_(event_);
        }
    private:
        std::function<void(std::shared_ptr<Event>)> handler_;
        std::shared_ptr<Event> event_;
    };

    // stores all the events fired from different threads
    // This needs to be thread safe
    class TaskQueue {
    public:
        void add(const Task &event);

        Task pull();

        bool empty() const { return events_.empty(); }
    private:
        std::list<Task> events_;
    };

}


#endif //HELLOWORLD_EVENTQUEUE_H
