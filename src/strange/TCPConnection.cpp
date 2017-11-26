//
// Created by malcolm on 26/11/17.
//

#include "TCPConnection.h"
#include <boost/asio.hpp>
#include <iostream>
#include <boost/bind.hpp>

boost::asio::ip::tcp::iostream& avenger::strange::TCPConnection::stream() {
  return stream_;
}

avenger::strange::TCPConnection::pointer
avenger::strange::TCPConnection::Create(avenger::strange::IOService& service) {
  return std::make_shared<avenger::strange::TCPConnection>(
      service.getService());
}

boost::asio::ip::tcp::socket& avenger::strange::TCPConnection::socket() {
  return socket_;
}

void avenger::strange::TCPConnection::debug() {
  static const std::string message_ = "Hello, World";

  boost::asio::async_write(
      socket(), boost::asio::buffer(message_),
      boost::bind(&TCPConnection::handleWrite, shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

avenger::strange::TCPConnection::TCPConnection(boost::asio::io_service& service)
    : service_{service}, socket_{service} {}

void avenger::strange::TCPConnection::handleWrite(
    const boost::system::error_code& ec,
    size_t transfered) {
  std::cout << "Sent message" << std::endl;
}
