#include "TaskQueue.h"

namespace avenger {
void TaskQueue::add(const Task& event) {
  events_.emplace_back(event);
}

Task TaskQueue::pull() {
  Task event = events_.front();
  events_.pop_back();
  return event;
}
}
