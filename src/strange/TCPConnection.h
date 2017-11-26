//
// Created by malcolm on 26/11/17.
//

#ifndef ARDUINONETWORKING_TCPCONNECTOR_H
#define ARDUINONETWORKING_TCPCONNECTOR_H

#include "shield/IOService.h"
#include <string>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace avenger {
namespace strange {
class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
 public:
  using pointer = std::shared_ptr<TCPConnection>;

  explicit TCPConnection(boost::asio::io_service& service);

  static pointer Create(IOService& service);

  boost::asio::ip::tcp::iostream& stream();
  boost::asio::ip::tcp::socket& socket();

  void handleWrite(const boost::system::error_code& ec, size_t transfered);

  void debug();

 private:
  boost::asio::ip::tcp::iostream stream_;
  boost::asio::ip::tcp::socket socket_;
  boost::asio::io_service& service_;
};
}
}

#endif  // ARDUINONETWORKING_TCPCONNECTOR_H
