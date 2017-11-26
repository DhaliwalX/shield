//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_TELEMATICSMONITOR_H
#define HELLOWORLD_TELEMATICSMONITOR_H
#include <shield/Bot.h>
#include "TelematicsCache.h"
namespace avenger {
namespace reed {

// keeps telematics about a bot up to date
// it regularly fires events for updating the UI
class TelematicsMonitor {
 public:
  explicit TelematicsMonitor(std::shared_ptr<Bot> bot);

  void update(Location location);

  BotTelematics getLastTelematics();

  Location sampleAveragePosition();
  Velocity sampleAverageVelocity();
 private:
  void initializeUpdate();
  void finalizeUpdate(const BotTelematics &telematics);

  TelematicsCache cache_;
  BotTelematics average_;
  size_t sampleCount_;
  std::shared_ptr<Bot> bot_;

  Duration getDurationTillLast(TimePointMs now);
};

}
}
#endif //HELLOWORLD_TELEMATICSMONITOR_H
