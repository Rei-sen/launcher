
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

MockConnection::MockConnection() : db(openOrCreateLocalDatabase()) {
  userId = 0;
}

int MockConnection::getUserId() { return userId; }

bool MockConnection::isConnected() { return true; }


bool MockConnection::updatePassword(std::string pass) {
  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;

  statusOfPrep = sqlite3_prepare_v2(
      db.get(),
      "update password UPDATE users SET password = ? WHERE users.id = ? ",
      -1, &myStatement, NULL);
  sqlite3_bind_text(myStatement, 1, pass.c_str(), -1, SQLITE_STATIC);
//  sqlite3_bind_text(myStatement, 2, pass.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(myStatement, 2, userId);

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

std::vector<std::string> MockConnection::getAllGames() {
  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;
  std::vector<std::string> gameNameList;

  statusOfPrep = sqlite3_prepare_v2(
      db.get(),
      "select * from games ",
      -1, &myStatement, NULL);

  if (statusOfPrep == SQLITE_OK) {
    int statusOfStep = sqlite3_step(myStatement);
    int id = 0;
    std::string name, description;
    double price;

    while (statusOfStep == SQLITE_ROW) {
      name = (char *)sqlite3_column_text(myStatement, 1);
      gameNameList.push_back(name);
      statusOfStep = sqlite3_step(myStatement);
      std::cout << "game: " << name << "\n";

    }
    sqlite3_finalize(myStatement);
    return gameNameList;
  
  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
  }
  // to tu będzie puste aka błąd jest
  return gameNameList;
}

std::vector<std::string> MockConnection::getAllDlc() {
  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;
  std::vector<std::string> gameDlcList;

  statusOfPrep = sqlite3_prepare_v2(db.get(), "select * from dlcs ", -1,
                                    &myStatement, NULL);

  if (statusOfPrep == SQLITE_OK) {
    int statusOfStep = sqlite3_step(myStatement);
    int id = 0;
    std::string name, description;
    double price;

    while (statusOfStep == SQLITE_ROW) {
      name = (char *)sqlite3_column_text(myStatement, 2);
      gameDlcList.push_back(name);
      statusOfStep = sqlite3_step(myStatement);
      std::cout << "dlc: " << name << "\n";
    }
    sqlite3_finalize(myStatement);
    return gameDlcList;


  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
  }
  // to tu będzie puste aka błąd jest
  return gameDlcList;
}


bool MockConnection::login(std::string name, std::string pass) {

  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;

  statusOfPrep = sqlite3_prepare_v2(
      db.get(), "select users.id from users where users.name = ? and users.password = ?", -1,
      &myStatement,
      NULL);
  sqlite3_bind_text(myStatement, 1, name.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(myStatement, 2, pass.c_str(), -1, SQLITE_STATIC);
    
     if (statusOfPrep == SQLITE_OK) {
       int statusOfStep = sqlite3_step(myStatement);
       int resoultCount = 0;
       int id = 0;
       while (statusOfStep == SQLITE_ROW) {
           id = sqlite3_column_int(myStatement, 0);
          std::cout << "Student Id: " << id << std::endl;
          statusOfStep = sqlite3_step(myStatement);
          resoultCount++;
       }
        sqlite3_finalize(myStatement);
        if (resoultCount == 1) {
            userId = id;
            return true;
        }
  } else {
          std::cout << "Problem creating a prepared statement" << std::endl;
  }
  //#warning zaimplementować



  return false;
}
bool MockConnection::registerAccount(std::string name, std::string pass) {
  sqlite3_stmt *myStatement;
  int statusOfPrep = 0;

  statusOfPrep = sqlite3_prepare_v2(
      db.get(),
      "select users.id from users where users.name = ? and users.password = ?",
      -1, &myStatement, NULL);
  sqlite3_bind_text(myStatement, 1, name.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(myStatement, 2, pass.c_str(), -1, SQLITE_STATIC);

  if (statusOfPrep == SQLITE_OK) {
    int statusOfStep = sqlite3_step(myStatement);
    int resoultCount = 0;
    int id = 0;
    while (statusOfStep == SQLITE_ROW) {
      id = sqlite3_column_int(myStatement, 0);
      std::cout << "Student Id: " << id << std::endl;

      statusOfStep = sqlite3_step(myStatement);
      resoultCount++;
    }
    sqlite3_finalize(myStatement);

    if (resoultCount == 0) {
      statusOfPrep = sqlite3_prepare_v2(
          db.get(),
          "insert into users (name, password, publisher) values(?, ?, 0) ", -1,
          &myStatement, NULL);
      sqlite3_bind_text(myStatement, 1, name.c_str(), -1, SQLITE_STATIC);
      sqlite3_bind_text(myStatement, 2, pass.c_str(), -1, SQLITE_STATIC);
      if (statusOfPrep == SQLITE_OK) {
        statusOfStep = sqlite3_step(myStatement);
        sqlite3_finalize(myStatement);

        login(name,pass);
        return true;
      }


    } else {
      std::cout << "Login taken";
    }
  } else {
    std::cout << "Problem creating a prepared statement" << std::endl;
  }
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
