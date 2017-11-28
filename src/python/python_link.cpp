#include <boost/python.hpp>
#include <shield/Runner.h>
#include <strange/TCPConnection.h>
#include <xavier/BotController.h>

using namespace boost::python;
using namespace avenger;

namespace {

void startWorkers() {
  char *argv[1] = { "python" };
  avenger::Runner::RunPythonThread(1, argv);
}

BOOST_PYTHON_MODULE (shield_cpp) {
  def("startWorkers", startWorkers);

  class_<xavier::BotController>("Controller")
      .def("moveToAndFro", &xavier::BotController::makeToAndFro)
          .def("moveForward", &xavier::BotController::moveForward)
              .def("moveBackward", &xavier::BotController::moveBackward)
                  .def("moveLeft", &xavier::BotController::turnLeft)
                      .def("moveRight", &xavier::BotController::turnRight);

}

}
