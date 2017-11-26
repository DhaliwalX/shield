//
// Created by malcolm on 26/11/17.
//

#ifndef ARDUINONETWORKING_SERVER_H
#define ARDUINONETWORKING_SERVER_H

#include <boost/asio/ip/tcp.hpp>
#include "IOService.h"
#include "TCPConnection.h"

namespace avenger {
    namespace strange {

        class Server {
        public:
            Server(IOService &service, unsigned short port);

            void startListening();

        private:
            void handleNewConnection(TCPConnection::pointer connection,
                            const boost::system::error_code &ec);

            // order matters here
            IOService &service_;
            boost::asio::ip::tcp::endpoint endpoint_;
            boost::asio::ip::tcp::acceptor acceptor_;

            void acceptConnection();
        };

    }
}

#endif //ARDUINONETWORKING_SERVER_H
