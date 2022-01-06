
#include "MockConnection.hh"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

const fs::path dbPath = "server/db.sqlt";
const fs::path sqlInitPath = "server/init.sql";

static MockConnection::db_ptr createLocalDatabase();
static MockConnection::db_ptr openLocalDatabase();
static MockConnection::db_ptr openOrCreateLocalDatabase();

MockConnection::MockConnection() : db(openOrCreateLocalDatabase()) {}

bool MockConnection::isConnected() { return true; }
bool MockConnection::login(std::string name, std::string pass) {

#warning zaimplementować
  return true;
}
std::optional<std::string> MockConnection::registerAccount(std::string name,
                                                           std::string pass) {
  if (name.empty() || pass.empty())
    return "Empty name or password";

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db.get(),
                         "insert into users (name, password)"
                         "values (?, ?);",
                         -1, &stmt, nullptr)) {
    return "Could not prepare sql statement";
  }
  sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, pass.c_str(), -1, SQLITE_STATIC);

  switch (sqlite3_step(stmt)) {
  default:
    using namespace std::string_literals;
    return sqlite3_errmsg(db.get());
  case SQLITE_DONE:
    sqlite3_finalize(stmt);

    return std::nullopt;
  }
}

bool MockConnection::updateGame(std::string title, std::string description,
                                int price) {
#warning zaimplementować
  return false;
}

bool MockConnection::updateNews(std::string gametitle, std::string title,
                                std::string content) {
#warning zaimplementować
  return false;
}

bool MockConnection::updateSocials(std::string medium, std::string link) {
#warning zaimplementować
  return false;
}

MockConnection::db_ptr createLocalDatabase() {
  auto db = openLocalDatabase();

  std::ifstream f("server/init.sql");
  std::stringstream buffer;
  buffer << f.rdbuf();

  sqlite3_exec(db.get(), buffer.str().c_str(), nullptr, nullptr, nullptr);

  return db;
}

static MockConnection::db_ptr openLocalDatabase() {
  sqlite3 *rawDB;
  int result = sqlite3_open("server/db.sqlt", &rawDB);
  MockConnection::db_ptr db(rawDB);

  if (result != SQLITE_OK) {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db.get())
              << std::endl;

    // throw
    return nullptr;
  }
  return db;
}

static MockConnection::db_ptr openOrCreateLocalDatabase() {
  if (fs::exists(dbPath))
    return openLocalDatabase();
  else
    return createLocalDatabase();
}
