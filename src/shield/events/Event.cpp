//
// Created by malcolm on 25/11/17.
//

#include "Event.h"

uint32_t avenger::Event::currentInstanceId_ = 0;

avenger::Event::Event() {
  id_ = currentInstanceId_++;
}

uint32_t avenger::Event::getId() {
  return id_;
}

void avenger::Event::Notify(std::shared_ptr<avenger::Event> event) {
  event->getMetadata()->notifyListeners(event);
}

void avenger::EventMetadata::registerListener(
    avenger::EventListener* listener) {
  listeners_.push_back(listener);
}

void avenger::EventMetadata::notifyListeners(
    std::shared_ptr<avenger::Event> event) {
  for (auto listener : listeners_) {
    listener->onEvent(event);
  }
}
