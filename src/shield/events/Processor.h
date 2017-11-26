//
// Created by malcolm on 26/11/17.
//

#ifndef HELLOWORLD_PROCESSOR_H
#define HELLOWORLD_PROCESSOR_H

#include <mutex>
#include <thread>
#include <condition_variable>
#include "TaskQueue.h"

namespace avenger {

// for processing events, it takes a event from event queue and processes it
// in a separate thread
class Processor {
 public:
  Processor();

  void nextTick(Task event);

  void startMonitoring();

  void waitExecuteLoop();

  void processOne();

 private:
  TaskQueue queue_;
  std::mutex lock_;
  std::condition_variable var_;
  bool more_;

  std::unique_ptr<std::thread> processorThread_;
};
}

#endif  // HELLOWORLD_PROCESSOR_H
