//
// Created by malcolm on 26/11/17.
//

#ifndef HELLOWORLD_CONNECTIONEVENT_H
#define HELLOWORLD_CONNECTIONEVENT_H

#include <shield/events/Event.h>
#include "TCPConnection.h"
#include "ConnectionEventListener.h"

namespace avenger {
namespace strange {

class ConnectionEvent : public Event {
 public:
  explicit ConnectionEvent(std::shared_ptr<TCPConnection> connection);

  EventMetadata* getMetadata() override;

  static std::shared_ptr<ConnectionEvent> Make(
      std::shared_ptr<TCPConnection> connection);

  TCPConnection::pointer getConnection();

  static void Init();

  static void Subscribe(ConnectionEventListener* listener);

 private:
  std::shared_ptr<TCPConnection> connection_;
  static std::unique_ptr<EventMetadata> metadata_;
};
}
}

#endif  // HELLOWORLD_CONNECTIONEVENT_H
