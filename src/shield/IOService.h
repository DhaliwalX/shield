//
// Created by malcolm on 26/11/17.
//

#ifndef ARDUINONETWORKING_IOSERVICE_H
#define ARDUINONETWORKING_IOSERVICE_H

#include <boost/asio/io_service.hpp>

namespace avenger {
namespace strange {
// simple wrapper over boost asio::io_service
class IOService {
 public:
  IOService();

  boost::asio::io_service& getService();

 private:
  boost::asio::io_service service_;
};
}
}

#endif  // ARDUINONETWORKING_IOSERVICE_H
