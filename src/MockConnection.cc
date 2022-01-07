
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

bool MockConnection::updateLoginInfo(std::string name, std::string pass) {
  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;

  statusOfPrep = sqlite3_prepare_v2(
      db.get(),
      "update password UPDATE users SET user = ? and password = ? WHERE users.id = ? ", -1,
      &myStatement, NULL);
  sqlite3_bind_text(myStatement, 1, pass.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(myStatement, 2, pass.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int64(myStatement, 3, userID.value());
  


  if (statusOfPrep == SQLITE_OK) {
    int statusOfStep = sqlite3_step(myStatement);
    int resoultCount = 0;
    int id = 0;

    sqlite3_finalize(myStatement);
    return true;
  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
    return false;
  }
  //#warning zaimplementować
  return false;


}


std::vector<GameInfo> MockConnection::getAllGames() {

  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;
  std::vector<GameInfo> gamesList;
  std::vector<DLCInfo> dlscList;

  if (sqlite3_prepare_v2(db.get(), "select * from games ", -1, &myStatement,
                         NULL) == SQLITE_OK) {
    int statusOfStep = sqlite3_step(myStatement);
    int64_t id = 0;
    std::string name, description;
    double price;

    while (statusOfStep == SQLITE_ROW) {
        // pobranie id gry
        id = sqlite3_column_int64(myStatement, 0);
        // pobranie wszystkich dlc bazując na id gry
      dlscList = getAllDlc(id);
      name = (char *)sqlite3_column_text(myStatement, 1);
      description = (char *)sqlite3_column_text(myStatement, 2);
      price = sqlite3_column_double(myStatement, 3);

      // dodanie do wektora wynikowego
      gamesList.push_back(GameInfo(id, name, description, price, dlscList));

      statusOfStep = sqlite3_step(myStatement);
    }
    sqlite3_finalize(myStatement);
    return gamesList;

  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
  }
  // to tu będzie puste aka błąd jest
  return gamesList;
}

std::vector<DLCInfo> MockConnection::getAllDlc(int64_t id) {
  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;
  std::vector<std::string> gameDlcList;
  std::vector<DLCInfo> dlcsList;
  statusOfPrep = sqlite3_prepare_v2(db.get(), "select * from dlcs where gameID = ?", -1, &myStatement,
                         NULL);
  sqlite3_bind_int64(myStatement, 1, id);

  if (statusOfPrep == SQLITE_OK) {

    int64_t id_dlc = 0;

    std::string title, description;
    double price;

    while (sqlite3_step(myStatement) == SQLITE_ROW) {
      id_dlc = sqlite3_column_int64(myStatement, 1);
      title = (char *)sqlite3_column_text(myStatement, 2);
      price = sqlite3_column_double(myStatement, 3);  
      
      dlcsList.push_back(DLCInfo(id, id_dlc, title, price));
      gameDlcList.push_back(title);
    }
    sqlite3_finalize(myStatement);
    return dlcsList;

  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
  }
  // to tu będzie puste aka błąd jest
  return dlcsList;
}

DLCInfo MockConnection::getDLCInfo(int64_t DlcID) {

  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;

  statusOfPrep =
      sqlite3_prepare_v2(db.get(), "select * from dlcs where dlcs.id = ?", -1,
                         &myStatement, NULL);
  sqlite3_bind_int64(myStatement, 1, DlcID);

  if (statusOfPrep == SQLITE_OK) {
    int64_t id_dlc = 0;
    int64_t id_game = 0;

    std::string title, description;
    double price;

    if (sqlite3_step(myStatement)) {
      id_game = sqlite3_column_int64(myStatement, 0);
      id_dlc = sqlite3_column_int64(myStatement, 1);
      title = (char *)sqlite3_column_text(myStatement, 2);
      price = sqlite3_column_double(myStatement, 3);

      sqlite3_finalize(myStatement);
      return DLCInfo(id_game, id_dlc, title, price);
    }
  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
  }
  return DLCInfo(0, 0, "error", 0);
  //    return gamesList;
}

std::vector<DLCInfo> MockConnection::getOwnedDlc(int64_t userID,
                                                 int64_t gameID) {
  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;
  std::vector<DLCInfo> dlcsList;
  statusOfPrep = sqlite3_prepare_v2(
      db.get(), "select * from dlcOwnership where userID = ? and gameID = ?",
      -1, &myStatement, NULL);
  sqlite3_bind_int64(myStatement, 1, userID);
  sqlite3_bind_int64(myStatement, 2, gameID);

  if (statusOfPrep == SQLITE_OK) {

    int64_t DlcID = 0;

    while (sqlite3_step(myStatement) == SQLITE_ROW) {
      DlcID = sqlite3_column_int64(myStatement, 2);
      dlcsList.push_back(getDLCInfo(DlcID));
    }
    sqlite3_finalize(myStatement);
    return dlcsList;

  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
  }
  // to tu będzie puste aka błąd jest
  return dlcsList;
}


GameInfo MockConnection::getGameInfo(int64_t gameID) {

  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;
  std::vector<DLCInfo> temp;

  statusOfPrep =
      sqlite3_prepare_v2(db.get(), "select * from games where games.id = ?",
                         -1, &myStatement, NULL);
  sqlite3_bind_int64(myStatement, 1, gameID);

  if (statusOfPrep == SQLITE_OK) {
    int64_t id_dlc = 0;
    int64_t id_game = 0;

    std::string name, description;
    double price;

    if (sqlite3_step(myStatement)) {
      id_game = sqlite3_column_int64(myStatement, 0);
      name = (char *)sqlite3_column_text(myStatement, 1);
      description = (char *)sqlite3_column_text(myStatement, 2);
      price = sqlite3_column_double(myStatement, 3);

      sqlite3_finalize(myStatement);
      return GameInfo(id_game, name, description, price, temp);
    }
  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
  }

  return GameInfo(0, "error", "error", 0, temp);
  //    return gamesList;
}

std::vector<GameInfo> MockConnection::getOwnedGames(int64_t userID) {
  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;
  std::vector<GameInfo> gamesList;
  std::vector<DLCInfo> dlscList;

  statusOfPrep = sqlite3_prepare_v2(
      db.get(), "select * from gameOwnership where gameOwnership.userID = ? ",
      -1, &myStatement, NULL);
  sqlite3_bind_int64(myStatement, 1, userID);


  if (statusOfPrep == SQLITE_OK) {
    int64_t gameID = 0;
    std::string name, description;
    double price;

    while (sqlite3_step(myStatement) == SQLITE_ROW) {
      gameID = sqlite3_column_int64(myStatement, 1);
      GameInfo temp = getGameInfo(gameID);
      dlscList = getOwnedDlc(userID, gameID);

      gamesList.push_back(
          GameInfo(temp.getID(), temp.getTitle(), temp.getDescription(), temp.getPrice(), dlscList));
    }
    sqlite3_finalize(myStatement);
    return gamesList;

  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
  }

  // to tu będzie puste aka błąd jest
  return gamesList;


}



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

bool MockConnection::updateNews(std::string gametitle, std::string title,
                                std::string content) {
//#warning zaimplementować
  return false;
}

bool MockConnection::updateSocials(std::string medium, std::string link) {
//#warning zaimplementować
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
