
#include "State.hh"

State::State(std::unique_ptr<Connection> &&connection)
    : connection(std::move(connection)) {
  update();
}

Connection &State::getConnection() { return *connection; }

void State::update() {
  user = connection->getUserInfo();
  allGames = connection->getAllGames();
}

std::vector<GameInfo> &State::getAllGames() { return allGames; }
