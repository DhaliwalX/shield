//
// Created by malcolm on 26/11/17.
//

#include "ConnectionEvent.h"

namespace avenger {
    namespace strange {

        ConnectionEvent::ConnectionEvent(std::shared_ptr<TCPConnection> connection)
            : connection_{std::move(connection)}
        { }

        EventMetadata *ConnectionEvent::getMetadata() {
            return metadata_.get();
        }

        void ConnectionEvent::Init() {
            metadata_ = std::make_unique<EventMetadata>();
        }

        void ConnectionEvent::Subscribe(ConnectionEventListener *listener) {
            metadata_->registerListener(listener);
        }

        TCPConnection::pointer ConnectionEvent::getConnection() {
            return connection_;
        }

        std::shared_ptr<ConnectionEvent> ConnectionEvent::Make(std::shared_ptr<TCPConnection> connection) {
            return std::make_shared<ConnectionEvent>(connection);
        }


    }

}