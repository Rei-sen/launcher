
#include "MockConnection.hh"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

#include "News.hh"
#include "PublisherInfo.hh"
#include "SocialMedia.hh"

namespace fs = std::filesystem;

const fs::path dbPath = "server/db.sqlt";
const fs::path sqlInitPath = "server/init.sql";

static MockConnection::db_ptr createLocalDatabase();
static MockConnection::db_ptr openLocalDatabase();
static MockConnection::db_ptr openOrCreateLocalDatabase();

MockConnection::MockConnection() : db(openOrCreateLocalDatabase()) {}

bool MockConnection::isConnected() { return true; }

bool MockConnection::login(std::string name, std::string pass) {
  //
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

std::vector<GameInfo> MockConnection::getAllGames() {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "select id, name, description, price "
                         "from games",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("getAllGames(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
  }

  std::vector<GameInfo> games;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    GameInfo::ID id = sqlite3_column_int64(stmt, 0);
    // rzutowanie na char * ponieważ sqlite zwraca unsigned char *
    games.emplace_back(id, (char *)sqlite3_column_text(stmt, 1),
                       (char *)sqlite3_column_text(stmt, 2),
                       sqlite3_column_double(stmt, 3), getAllGamesDLCs(id));
  }

  sqlite3_finalize(stmt);

  return games;
}


std::vector<SocialMedia> MockConnection::getAllMedias() {
  sqlite3_stmt *stmt;
  /*
  create table 'socialMedias' (
       'id' integer primary key autoincrement,
       'name' text not null,
       'address' text not null
);

insert into 'socialMedias' (name, address)
values ('abc', 'abc.def');

  */




  if (sqlite3_prepare_v2(db.get(),
                         "select name, address "
                         "from socialMedias",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("getAllMedias(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
  }

  std::vector<SocialMedia> medias;
  while (sqlite3_step(stmt) == SQLITE_ROW) {

    // rzutowanie na char * ponieważ sqlite zwraca unsigned char *
    medias.emplace_back((char *)sqlite3_column_text(stmt, 0),
                      (char *)sqlite3_column_text(stmt, 1));
  }

  sqlite3_finalize(stmt);

  return medias;
}

std::vector<DLCInfo> MockConnection::getAllGamesDLCs(GameInfo::ID id) {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "select id, title, price "
                         "from dlcs "
                         "where gameID = ?;",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error(
        "getAllGamesDLCs(): could not prepare statement"s +
        sqlite3_errmsg(db.get()));
  }

  sqlite3_bind_int64(stmt, 1, id);

  std::vector<DLCInfo> dlcs;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    dlcs.emplace_back(id, sqlite3_column_int64(stmt, 0),
                      (char *)sqlite3_column_text(stmt, 1),
                      sqlite3_column_double(stmt, 2));
  }

  sqlite3_finalize(stmt);

  return dlcs;
}

std::unique_ptr<UserInfo> MockConnection::getUserInfo() {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "select publisher "
                         "from users "
                         "where id = ?;",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("getUserInfo(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
  }

  sqlite3_bind_int64(stmt, 1, userID.value());

  bool isPublisher = sqlite3_column_int(stmt, 0);
  sqlite3_finalize(stmt);

  if (isPublisher)
    return std::make_unique<PublisherInfo>(getOwnedGames(), getOwnedDLCs(),
                                           userID.value());
  else
    return std::make_unique<UserInfo>(getOwnedGames(), getOwnedDLCs(),
                                      userID.value());
}

std::vector<GameInfo::ID> MockConnection::getOwnedGames() {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "select gameID "
                         "from gameOwnership "
                         "where userID = ?;",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("getOwnedGames(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
  }

  sqlite3_bind_int64(stmt, 1, userID.value());

  std::vector<GameInfo::ID> gameIDs;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    gameIDs.push_back(sqlite3_column_int64(stmt, 0));
  }
  sqlite3_finalize(stmt);

  return gameIDs;
}

std::vector<std::pair<GameInfo::ID, DLCInfo::ID>>
MockConnection::getOwnedDLCs() {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "select gameID, dlcID "
                         "from dlcOwnership "
                         "where userID = ?;",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("getOwnedDLCs(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
  }

  sqlite3_bind_int64(stmt, 1, userID.value());

  std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> ownedDLCs;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    ownedDLCs.push_back(std::make_pair(sqlite3_column_int64(stmt, 0),
                                       sqlite3_column_int64(stmt, 1)));
  }
  sqlite3_finalize(stmt);

  return ownedDLCs;
}

//
std::vector<News> MockConnection::getAllNews() {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "SELECT gameID, id, title, content "
                         "FROM news",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("getAllNews(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
  }

  std::vector<News> news;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    GameInfo::ID id = sqlite3_column_int64(stmt, 0);
    // rzutowanie na char * ponieważ sqlite zwraca unsigned char *
    news.emplace_back(id, sqlite3_column_int64(stmt, 1),
                       (char *)sqlite3_column_text(stmt, 2),
                      (char *)sqlite3_column_text(stmt, 3));
  }

  sqlite3_finalize(stmt);

  return news;
}

bool MockConnection::updateUserLoginPassword(std::string uName,
                                             std::string uPassword) {
  sqlite3_stmt *stmt;
//  userID;
    if (sqlite3_prepare_v2(db.get(),
                         "update users "
                         "set name = ?, password = ? "
                         "where id = ?;",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("updateUserLoginPassword(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
    return false;
  }

  sqlite3_bind_text(stmt, 1, uName.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, uPassword.c_str(), -1,
                    SQLITE_TRANSIENT);
  sqlite3_bind_int64(stmt, 3, userID.value());

  auto result = sqlite3_step(stmt);

  sqlite3_finalize(stmt);
  
  return result == SQLITE_DONE;
}

bool MockConnection::updateGameInfo(GameInfo info) {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "update games "
                         "set name = ?, description = ?, price = ? "
                         "where id = ?;",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("getOwnedDLCs(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
    return false;
  }
  // transient bo stringi są dealokowane po wywołaniu funkcji
  sqlite3_bind_text(stmt, 1, info.getTitle().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, info.getDescription().c_str(), -1,
                    SQLITE_TRANSIENT);
  sqlite3_bind_double(stmt, 3, info.getPrice());
  sqlite3_bind_int64(stmt, 4, info.getID());

  auto result = sqlite3_step(stmt);

  sqlite3_finalize(stmt);

  return result == SQLITE_DONE;
}

bool MockConnection::updateNewsInfo(News info) {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "update news "
                         "set title = ?, content = ?"
                         "where id = ? and gameID = ?;",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("updateNewsInfo(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
    return false;
  }
  // transient bo stringi są dealokowane po wywołaniu funkcji
  sqlite3_bind_text(stmt, 1, info.getTitle().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, info.getContent().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int64(stmt, 3, info.getID());
  sqlite3_bind_int64(stmt, 4, info.getGameID());

  auto result = sqlite3_step(stmt);

  return result == SQLITE_DONE;
}

bool MockConnection::updateMediaInfo(SocialMedia info) { 
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "update socialMedias "
                         "set name = ?, address = ?"
                         "where name = ?;",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("updateNewsInfo(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
    return false;
  }
  // transient bo stringi są dealokowane po wywołaniu funkcji
  sqlite3_bind_text(stmt, 1, info.getName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, info.getAddress().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, info.getName().c_str(), -1, SQLITE_TRANSIENT);

  auto result = sqlite3_step(stmt);

  return result == SQLITE_DONE;
}

std::optional<std::string> MockConnection::addNewsInfo(GameInfo::ID gid,
                                                       std::string title,
                                                       std::string content) {
  sqlite3_stmt *stmt;
  ///weird stuff
  if (sqlite3_prepare_v2(db.get(),
                         "select MAX(id) "
                         "from news "
                         "where gameID = ?;",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("addNewsInfo(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
  }

  sqlite3_bind_int64(stmt, 1, gid);
News::ID newsid=1; //I dont know how to do it better but at least it works now 
  if (sqlite3_step(stmt) == SQLITE_ROW) {
  newsid = sqlite3_column_int64(stmt, 0) + 1;
  }
  sqlite3_finalize(stmt);

  if (sqlite3_prepare_v2(db.get(),
                         "insert into news (gameID,id, title,content) "
                         "values(?,?, ?, ?);",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("addNewsInfo(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
    return sqlite3_errmsg(db.get());
  }
  sqlite3_bind_int64(stmt, 1, gid);
  sqlite3_bind_int64(stmt, 2, newsid);
  sqlite3_bind_text(stmt, 3, title.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 4, content.c_str(), -1, SQLITE_TRANSIENT);

  auto result = sqlite3_step(stmt);

  sqlite3_finalize(stmt);

  if (result == SQLITE_DONE)
    return std::nullopt;
  else
    return sqlite3_errmsg(db.get());
}

std::optional<std::string> MockConnection::addMedia(SocialMedia medium) {
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db.get(),
                         "insert into socialMedias (name, address) "
                         "values(?,?);",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("addMedia(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
    return sqlite3_errmsg(db.get());
  }
  sqlite3_bind_text(stmt, 1, medium.getName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, medium.getAddress().c_str(), -1, SQLITE_TRANSIENT);

    auto result = sqlite3_step(stmt);

  sqlite3_finalize(stmt);

  if (result == SQLITE_DONE)
    return std::nullopt;
  else
    return sqlite3_errmsg(db.get());
}

std::optional<std::string> MockConnection::buyGame(GameInfo::ID id) {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "insert into gameOwnership (userID, gameID) "
                         "values(?, ?);",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("buyGame(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
    return sqlite3_errmsg(db.get());
  }
  "select max(id) from news where gameID == ?";
  sqlite3_bind_int64(stmt, 1, userID.value());
  sqlite3_bind_int64(stmt, 2, id);

  auto result = sqlite3_step(stmt);

  sqlite3_finalize(stmt);

  if (result == SQLITE_DONE)
    return std::nullopt;
  else
    return sqlite3_errmsg(db.get());
}

std::optional<std::string> MockConnection::buyDLC(GameInfo::ID gameId,
                                                  DLCInfo::ID id) {
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db.get(),
                         "insert into dlcOwnership (userID, gameID, dlcID) "
                         "values(?, ?, ?);",
                         -1, &stmt, nullptr)) {
    using namespace std::string_literals;
    throw std::runtime_error("buyGame(): could not prepare statement"s +
                             sqlite3_errmsg(db.get()));
    return sqlite3_errmsg(db.get());
  }

  sqlite3_bind_int64(stmt, 1, userID.value());
  sqlite3_bind_int64(stmt, 2, gameId);
  sqlite3_bind_int64(stmt, 3, id);

  auto result = sqlite3_step(stmt);

  sqlite3_finalize(stmt);

  if (result == SQLITE_DONE)
    return std::nullopt;
  else
    return sqlite3_errmsg(db.get());
}

static MockConnection::db_ptr createLocalDatabase() {
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
