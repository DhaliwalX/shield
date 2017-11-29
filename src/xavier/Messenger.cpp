#include "Messenger.h"

int avenger::xavier::Messenger::counter_ = 0;

std::shared_ptr<avenger::xavier::Messenger> avenger::xavier::Messenger::Make(std::shared_ptr<avenger::strange::TCPConnection> conn) {
  auto messenger = std::make_shared<Messenger>();
  messenger->connection = conn;
  return messenger;
}
