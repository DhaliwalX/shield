//
// Created by malcolm on 28/11/17.
//

#ifndef SHIELD_RUNNER_H
#define SHIELD_RUNNER_H

#include <thread>

namespace avenger {

class Runner {
 public:
  static int Run(int argc, char **argv);

  static std::unique_ptr<std::thread> thread_;

  static void RunPythonThread(int argc, char **argv);
};

}

#endif //SHIELD_RUNNER_H
