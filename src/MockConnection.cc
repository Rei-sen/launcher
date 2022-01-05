
#include "MockConnection.hh"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

#if defined(WIN32) || defined(_WIN32) ||                                      \
    defined(__WIN32) && !defined(__CYGWIN__)
const fs::path dbPath = "../../../server/db.sqlt";
const fs::path sqlInitPath = "../../../server/init.sql";

#else
const fs::path dbPath = "server/db.sqlt";
const fs::path sqlInitPath = "server/init.sql";
#endif

static MockConnection::db_ptr createLocalDatabase();
static MockConnection::db_ptr openLocalDatabase();
static MockConnection::db_ptr openOrCreateLocalDatabase();

MockConnection::MockConnection() : db(openOrCreateLocalDatabase()) {}

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

MockConnection::db_ptr createLocalDatabase() {
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

  return MockConnection::db_ptr(db);
}

static MockConnection::db_ptr openLocalDatabase() {
  sqlite3 *db;
  int result = sqlite3_open("server/db.sqlt", &db);

  if (result != SQLITE_OK) {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);

    // throw
    return nullptr;
  }
  return MockConnection::db_ptr(db);
}

static MockConnection::db_ptr openOrCreateLocalDatabase() {
  if (fs::exists(dbPath))
    return openLocalDatabase();
  else
    return createLocalDatabase();
}
