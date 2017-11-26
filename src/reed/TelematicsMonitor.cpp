//
// Created by malcolm on 27/11/17.
//

#include <shield/events/dispatcher.h>

#include <utility>
#include "TelematicsMonitor.h"
#include "TelematicsEvent.h"

namespace avenger {
namespace reed {

TelematicsMonitor::TelematicsMonitor(std::shared_ptr<Bot> bot)
    : cache_{}, average_{}, bot_{std::move(bot)}
{ }

void TelematicsMonitor::update(Location location) {
  initializeUpdate();

  BotTelematics telematics{};

  // calculate velocity
  TimePointMs now = Clock::now();
  Duration duration = getDurationTillLast(now);
  Velocity velocity = calculateVelocity(location,
                                        getLastTelematics().location,
                                        duration);

  telematics.velocity = velocity;
  telematics.timeStamp = now;
  telematics.location = location;

  cache_.add(telematics);

  finalizeUpdate(telematics);

  auto event = TelematicsEvent::Make(bot_, telematics);
  dispatch(SHIELD::GetInstance(), event);
}

BotTelematics TelematicsMonitor::getLastTelematics() {
  return cache_.empty() ? BotTelematics{} : cache_.getLatest();
}

void TelematicsMonitor::initializeUpdate() {
  sampleCount_++;
}

Duration TelematicsMonitor::getDurationTillLast(TimePointMs now) {
  auto last = getLastTelematics();
  return now - last.timeStamp;
}

void TelematicsMonitor::finalizeUpdate(const BotTelematics &telematics) {

}

Location TelematicsMonitor::sampleAveragePosition() {
  Location location{};

  if (cache_.empty())
    return location;

  for (const auto &telematics : cache_.cache()) {
    location.x += telematics.location.x;
    location.y += telematics.location.y;
  }

  location.x /= cache_.size();
  location.y /= cache_.size();
  return location;
}

Velocity TelematicsMonitor::sampleAverageVelocity() {
  Velocity velocity{};

  if (cache_.empty()) {
    return velocity;
  }

  for (const auto &telematics : cache_.cache()) {
    velocity.vx += telematics.velocity.vx;
    velocity.vy += telematics.velocity.vy;
  }

  velocity.vx /= cache_.size();
  velocity.vy /= cache_.size();
  return velocity;
}

}
}