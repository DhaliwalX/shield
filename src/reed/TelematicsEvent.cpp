//
// Created by malcolm on 27/11/17.
//

#include <cassert>
#include "TelematicsEvent.h"

namespace avenger {
namespace reed {

std::unique_ptr<EventMetadata> TelematicsEvent::metadata_{};

void TelematicsEventListener::onEvent(std::shared_ptr<Event> event) {
  onUpdate(std::dynamic_pointer_cast<TelematicsEvent>(event));
}

TelematicsEvent::TelematicsEvent(std::shared_ptr<Bot> bot,
                                 BotTelematics botTelematics)
    : telematics_{ botTelematics }, bot_{ bot }
{}

EventMetadata *TelematicsEvent::getMetadata() {
  return metadata_.get();
}

std::shared_ptr<TelematicsEvent>
TelematicsEvent::Make(std::shared_ptr<Bot> bot, BotTelematics telematics) {
  return std::make_shared<TelematicsEvent>(bot, telematics);
}

void TelematicsEvent::Init() {
  metadata_ = std::make_unique<EventMetadata>();
}

void TelematicsEvent::Subscribe(TelematicsEventListener *listener) {
  metadata_->registerListener(listener);
}

void TelematicsEventMetadata::notifyListeners(std::shared_ptr<Event> event) {
  auto telematicsEvent = std::dynamic_pointer_cast<TelematicsEvent>(event);
  assert(telematicsEvent && "telematics event should not be nullptr.");

  for (auto listener : listeners_) {
    auto telematicsListener = dynamic_cast<TelematicsEventListener*>(listener);

    if (!telematicsListener) {
      continue;
    }

    if (telematicsListener->bot() == telematicsEvent->bot()) {
      telematicsListener->onUpdate(telematicsEvent);
    }
  }
}

}
}
