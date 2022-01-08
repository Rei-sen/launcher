
#include "State.hh"

State::State(std::unique_ptr<Connection> &&connection)
    : connection(std::move(connection)) {
  update();
}

Connection &State::getConnection() { return *connection; }

void State::update() {
  user = connection->getUserInfo();
  // dlcs = connection->getAllDLCs();
  // allGames = connection->getAllGames();
}
