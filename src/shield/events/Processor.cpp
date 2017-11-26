//
// Created by malcolm on 26/11/17.
//

#include <iostream>
#include "Processor.h"

avenger::Processor::Processor() {}

void avenger::Processor::nextTick(Task event) {
  std::unique_lock<std::mutex> lk(lock_);
  queue_.add(event);
  more_ = true;
  var_.notify_one();
}

void avenger::Processor::startMonitoring() {
  processorThread_ =
      std::make_unique<std::thread>([this] { waitExecuteLoop(); });
}

void avenger::Processor::waitExecuteLoop() {
  {
    while (true) {
      std::unique_lock<std::mutex> lk(lock_);
      var_.wait(lk);

      while (more_) {
        processOne();
      }
    }
  }
}

void avenger::Processor::processOne() {
  if (queue_.empty()) {
    more_ = false;
    return;
  }
  auto task = queue_.pull();
  task.execute();
}
