//
// Created by malcolm on 26/11/17.
//

#include "SHIELD.h"
#include <hawkeye/Camera.h>
#include <SkGraphics.h>

namespace avenger {
SHIELD* SHIELD::shield;

void SHIELD::Init() {
  shield = new SHIELD();

  // start the event handling system
  shield->eventProcessor_.startMonitoring();

  if (!avenger::hawkeye::Camera::TryInstall(0)) {
    fprintf(stderr, "Unable to start camera. Init failed");
    exit(EXIT_FAILURE);
  }
  avenger::hawkeye::Camera::StartCapturing();
  SkGraphics::Init();
}

void SHIELD::Destroy() {
  delete shield;
}

SHIELD::SHIELD() = default;

SHIELD::~SHIELD() = default;

void SHIELD::postEvent(std::shared_ptr<Event> evt) {
  auto handler = std::function<void(std::shared_ptr<Event>)>(
      [](std::shared_ptr<Event> event) { Event::Notify(event); });
  Task task(evt, handler);
  eventProcessor_.nextTick(task);
}

SHIELD* SHIELD::GetInstance() {
  return shield;
}
}
