//
// Created by malcolm on 26/11/17.
//

#ifndef HELLOWORLD_SHIELD_H
#define HELLOWORLD_SHIELD_H

#include <shield/events/Processor.h>
#include <reed/Reed.h>
#include "shield/events/Event.h"

namespace avenger {

// used for storing global and various other utility information
// like state of the application.
class SHIELD {
 public:
  static const int kSHIELDCameraWidth = 640;
  static const int kSHIELDCameraHeight = 360;

  SHIELD();

  ~SHIELD();

  void postEvent(std::shared_ptr<Event> event);

  static void Init();
  static void Destroy();
  static SHIELD* GetInstance();

  auto &reed() { return reedRef_; }
 private:
  Processor eventProcessor_;
  reed::HandleReed reedRef_;
  static SHIELD* shield;
};
}

#endif  // HELLOWORLD_SHIELD_H
