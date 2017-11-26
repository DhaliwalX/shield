//
// Created by malcolm on 26/11/17.
//

#include "ConnectionEventListener.h"
#include "ConnectionEvent.h"

void avenger::strange::ConnectionEventListener::onEvent(
    std::shared_ptr<avenger::Event> event) {
  onNewConnection((std::dynamic_pointer_cast<ConnectionEvent>(event)));
}
