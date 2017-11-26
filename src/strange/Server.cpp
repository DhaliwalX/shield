//
// Created by malcolm on 26/11/17.
//

#include "Server.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <utility>
#include <shield/SHIELD.h>
#include <shield/events/dispatcher.h>
#include "TCPConnection.h"
#include "ConnectionEvent.h"

using namespace boost::asio::ip;
namespace avenger {
namespace strange {

Server::Server(avenger::strange::IOService& service, unsigned short port)
    : service_{service},
      endpoint_(tcp::v4(), port),
      acceptor_(service.getService(), endpoint_) {}

void Server::handleNewConnection(TCPConnection::pointer connection,
                                 const boost::system::error_code& error_code) {
  if (error_code) {
    fprintf(stderr, "ConnectionError:%s:%d: %s\n", __FILE__, __LINE__,
            error_code.message().c_str());
    return;
  }
  auto event = ConnectionEvent::Make(std::move(connection));
  dispatch(SHIELD::GetInstance(), event);

  // wait for next connection
  acceptConnection();
}

void Server::acceptConnection() {
  auto connection = TCPConnection::Create(service_);

  acceptor_.async_accept(
      connection->socket(),
      boost::bind(&Server::handleNewConnection, this, connection,
                  boost::asio::placeholders::error));
}

void Server::startListening() {
  acceptConnection();
}
}
}
