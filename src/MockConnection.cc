
#include "MockConnection.hh"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

namespace fs = std::filesystem;

const fs::path dbPath = "server/db.sqlt";
const fs::path sqlInitPath = "server/init.sql";

static MockConnection::db_ptr createLocalDatabase();
static MockConnection::db_ptr openLocalDatabase();
static MockConnection::db_ptr openOrCreateLocalDatabase();

MockConnection::MockConnection() : db(openOrCreateLocalDatabase()) {}

bool MockConnection::isConnected() { return true; }

bool MockConnection::login(std::string name, std::string pass) {

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db.get(),
                         "select id, name, password "
                         "from users "
                         "where name = ?;",
                         -1, &stmt, nullptr)) {
    return false;
  }

  sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return false;
  }

  if (pass != reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)))
    return false;

  userID = sqlite3_column_int64(stmt, 0);
  return true;
}

bool MockConnection::isLoggedIn() { return userID.has_value(); }

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
//#warning zaimplementować
  return false;
}

bool MockConnection::updateNews(std::string gamename, std::string title,
                                std::string content) {
//#warning zaimplementować
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db.get(),
                         "select id "
                         "from games "
                         "where name = ?;",
                         -1, &stmt, nullptr)) {
    return false;
  }
  sqlite3_bind_text(stmt, 1, gamename.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return false;
  }
  long id = sqlite3_column_int64(stmt, 0);

  if (sqlite3_prepare_v2(db.get(),
                         "select id "
                         "from games "
                         "where name = ?;",
                         -1, &stmt, nullptr)) {
    return false;
  }

  return false;
}

bool MockConnection::updateSocials(std::string medium, std::string link) {
//#warning zaimplementować
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db.get(),
                         "select name, adress "
                         "from socialMedias "
                         "where name = ?;",
                         -1, &stmt, nullptr)) {
    return false;
  }
  sqlite3_bind_text(stmt, 1, medium.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return false;
  }
  sqlite3_stmt *stmt2;
  if (sqlite3_prepare_v2(db.get(),
                         "update socialMedias "
                         "set adress = ? "
                         "where name = ?;",
                         -1, &stmt, nullptr)) {
    return false;
  }
  sqlite3_bind_text(stmt, 1, link.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, medium.c_str(), -1, SQLITE_STATIC);

  switch (sqlite3_step(stmt)) {
  default:
    return false;
  case SQLITE_DONE:
    sqlite3_finalize(stmt);
    return true;
  }

  return false;
}

bool MockConnection::addSocials(std::string medium, std::string link) {
  //#warning zaimplementować
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db.get(),
                         "select name,  "
                         "from socialMedias "
                         "where name = ?;",
                         -1, &stmt, nullptr)) {
    return false;
  }
  sqlite3_bind_text(stmt, 1, medium.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) == SQLITE_ROW) {//tutaj kod który sprawia że funkcja nic nie zmienia jeśli social medium już istnieje
    sqlite3_finalize(stmt);
  } else
    return false;

  sqlite3_stmt *stmt2;
  if (sqlite3_prepare_v2(db.get(),
                         "insert into socialMedias "
                         "(name, address)values(?,?);",
                         -1, &stmt, nullptr)) {
    return false;
  }
  sqlite3_bind_text(stmt, 1, medium.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, link.c_str(), -1, SQLITE_STATIC);

  switch (sqlite3_step(stmt)) {
  default:
    return false;
  case SQLITE_DONE:
    sqlite3_finalize(stmt);
    return true;
  }

  return false;
}

std::unique_ptr<UserInfo> MockConnection::getUserInfo() {
  sqlite3_stmt *isPublisherStmt;
  sqlite3_stmt *gameOwnershipStmt;
  sqlite3_stmt *dlcOwnershipStmt;
  if (sqlite3_prepare_v2(db.get(),
                         "select publisher "
                         "from users "
                         "where id = ?;",
                         -1, &isPublisherStmt, nullptr) ||
      sqlite3_prepare_v2(db.get(),
                         "select gameID "
                         "from gameOwnership "
                         "where userID = ?;",
                         -1, &gameOwnershipStmt, nullptr) ||
      sqlite3_prepare_v2(db.get(),
                         "select gameID, dlcID "
                         "from dlcOwnership "
                         "where userID = ?;",
                         -1, &dlcOwnershipStmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
  }

  sqlite3_bind_int64(isPublisherStmt, 1, userID.value());
  sqlite3_bind_int64(gameOwnershipStmt, 1, userID.value());
  sqlite3_bind_int64(dlcOwnershipStmt, 1, userID.value());

  std::vector<GameInfo::ID> ownedGames;
  while (sqlite3_step(gameOwnershipStmt) == SQLITE_ROW) {
    ownedGames.push_back(sqlite3_column_int64(gameOwnershipStmt, 0));
  }
  sqlite3_finalize(gameOwnershipStmt);

  std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> ownedDLCs;
  while (sqlite3_step(dlcOwnershipStmt) == SQLITE_ROW) {
    ownedDLCs.push_back(
        std::make_pair(sqlite3_column_int64(dlcOwnershipStmt, 0),
                       sqlite3_column_int64(dlcOwnershipStmt, 1)));
  }
  sqlite3_finalize(dlcOwnershipStmt);

  bool isPublisher = sqlite3_column_int(isPublisherStmt, 0);
  sqlite3_finalize(isPublisherStmt);

//#warning "dodac klase PublisherInfo"
  return std::make_unique<UserInfo>(ownedGames, ownedDLCs);
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
