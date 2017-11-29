#include <boost/python.hpp>
#include <shield/Runner.h>
#include <strange/TCPConnection.h>
#include <xavier/BotController.h>
#include <reed/Reed.h>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;
using namespace avenger;

namespace {
template<class T>
struct VecToList
{
  static PyObject* convert(const std::vector<T>& vec)
  {
    boost::python::list* l = new boost::python::list();
    for(size_t i = 0; i < vec.size(); i++) {
      l->append(vec[i]);
    }

    return l->ptr();
  }
};

void startWorkers() {
  char *argv[1] = { "python" };
  avenger::Runner::RunPythonThread(1, argv);
}

BOOST_PYTHON_MODULE (shield_cpp) {

//  boost::python::to_python_converter<reed::BotContainer, VecToList<reed::PyBot>>();
  def("startWorkers", startWorkers);

  class_<reed::BotContainer>("BotContainer")
      .def(vector_indexing_suite<reed::BotContainer>());

  class_<reed::Location>("Location")
      .def_readonly("x", &reed::Location::x)
          .def_readonly("y", &reed::Location::y)
              .def_readonly("r", &reed::Location::r);

  class_<reed::Velocity>("Velocity")
      .def_readonly("vx", &reed::Velocity::vx)
          .def_readonly("vy", &reed::Velocity::vy);

  class_<reed::HandleReed>("Reed")
      .def("startServer", &reed::HandleReed::startService)
          .def("getControllers", &reed::HandleReed::getPythonControllers);

  class_<reed::PyBot>("PyBot")
      .def("moveToAndFro", &reed::PyBot::poll)
          .def("moveForward", &reed::PyBot::moveForward)
              .def("moveBackward", &reed::PyBot::moveBack)
                  .def("moveLeft", &reed::PyBot::turnLeft)
                      .def("moveRight", &reed::PyBot::turnRight)
                          .def("getIP", &reed::PyBot::getIP)
                              .def("getLocation", &reed::PyBot::getCurrentLocation)
                                  .def("getVelocity", &reed::PyBot::getCurrentVelocity);

}

}
