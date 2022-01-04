
#include "MockConnection.hh"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include <sqlite3.h>

// zamienić potem na unique_ptr
static sqlite3 *createLocalDatabase();

MockConnection::MockConnection() {
  // sprawdzić czy istnieje
  // if (exists) {
  //
  //}
  // else {
  auto db = createLocalDatabase();
  sqlite3_close(db); // usunąć potem
  //}
}

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

static sqlite3 *createLocalDatabase() {
  sqlite3 *db;
  int result = sqlite3_open("server/db.sqlt", &db);

  if (result != SQLITE_OK) {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);

    // throw
    return nullptr;
  }

  std::ifstream f("server/init.sql");
  std::stringstream buffer;
  buffer << f.rdbuf();

  sqlite3_exec(db, buffer.str().c_str(), nullptr, nullptr, nullptr);

  return db;
}
