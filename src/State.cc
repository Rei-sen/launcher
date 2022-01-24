
#include "State.hh"

State::State(std::unique_ptr<Connection> &&connection)
    : connection(std::move(connection)) {
  update();
}

Connection &State::getConnection() { return *connection; }

void State::update() {
  user = connection->getUserInfo();
  allGames = connection->getAllGames();
  allNews = connection->getAllNews();
  allMedias = connection->getAllMedias();
  ownedDLCs = connection->getOwnedDLCs();
  ownedGames = connection->getOwnedGames();
}

std::vector<GameInfo::ID> &State::getOwnedGames() { return ownedGames; }
std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> &State::getOwnedDLCs() { return ownedDLCs; }
std::vector<GameInfo> &State::getAllGames() { return allGames; }
std::vector<News> &State::getAllNews() { return allNews; }
std::vector<SocialMedia> &State::getAllMedias() { return allMedias; }
UserInfo &State::getUser() { return *user; }