//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_TELEMATICSEVENT_H
#define HELLOWORLD_TELEMATICSEVENT_H

#include <shield/events/Event.h>
#include <reed/telemetics/BotTelematics.h>
#include <shield/Bot.h>

namespace avenger {
namespace reed {

class TelematicsEvent;

class TelematicsEventListener : public EventListener {
 public:
  virtual void onUpdate(std::shared_ptr<TelematicsEvent> event) = 0;
  void onEvent(std::shared_ptr<Event> event) final;
};

class TelematicsEvent : public Event {
 public:
  TelematicsEvent(std::shared_ptr<Bot> bot, BotTelematics botTelematics);

  BotTelematics &telematics() { return telematics_; }
  std::shared_ptr<Bot> &bot() { return bot_; }

  EventMetadata *getMetadata() override;

  static std::shared_ptr<TelematicsEvent> Make(std::shared_ptr<Bot> bot,
                                               BotTelematics telematics);
  static void Init();

  static void Subscribe(TelematicsEventListener *listener);
 private:
  BotTelematics telematics_;
  std::shared_ptr<Bot> bot_;

  static std::unique_ptr<EventMetadata> metadata_;
};

}
}

#endif //HELLOWORLD_TELEMATICSEVENT_H
