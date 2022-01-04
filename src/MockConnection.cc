
#include "MockConnection.hh"

bool MockConnection::isConnected() { return true; }
bool MockConnection::login(std::string name, std::string pass) {

//#warning zaimplementować
  return true;
}
bool MockConnection::registerAccount(std::string name, std::string pass) {

//#warning zaimplementować
  return false;
}

bool MockConnection::updateGame(std::string title, std::string description,
                                int price) {
  //#warning zaimplementować
  return false;
}

bool MockConnection::updateNews(std::string gametitle, std::string title,
                                std::string content) {
  return false;
}

bool MockConnection::updateSocials(std::string medium, std::string link) {
  //#warning zaimplementować
  return false;
}
