//
// Created by malcolm on 27/11/17.
//

#ifndef HELLOWORLD_TELEMETICSCACHE_H
#define HELLOWORLD_TELEMETICSCACHE_H

#include <boost/circular_buffer.hpp>
#include <reed/telemetics/BotTelematics.h>
namespace avenger {
namespace reed {

class TelematicsCache {
 public:
  static const size_t kMaxCacheSize = 5;

  TelematicsCache()
      : cache_(kMaxCacheSize)
  { }

  auto cache() { return cache_; }

  void add(BotTelematics telematics) {
    cache_.push_back(telematics);
  }

  bool empty() { return cache_.empty(); }
  size_t size() { return cache_.size(); }

  BotTelematics &getLatest() { return cache_.back(); }
 private:
  boost::circular_buffer<BotTelematics> cache_;
};

}
}

#endif //HELLOWORLD_TELEMETICSCACHE_H
