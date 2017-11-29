//
// Created by malcolm on 26/11/17.
//

#include <iostream>
#include <chrono>
#include "shield/timer/Time.h"
#include "Processor.h"

avenger::Processor::Processor() {}

void avenger::Processor::nextTick(Task event) {
  queue_.add(event);
  more_ = true;
  var_.notify_one();
}

void avenger::Processor::startMonitoring() {
  processorThread_ =
      std::make_unique<std::thread>([this] { waitExecuteLoop(); });
}

void avenger::Processor::waitExecuteLoop() {
    while (!shouldStop) {
      // wait for some task
      while (queue_.empty());

      // process one
      processOne();
    }
}

void avenger::Processor::processOne() {
  auto task = queue_.pull();
  task.execute();
}

avenger::Processor::~Processor() {
  shouldStop = true;
  processorThread_->join();
}
