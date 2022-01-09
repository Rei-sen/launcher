
#pragma once

#include <sqlite3.h>

#include "Connection.hh"
#include "UserInfo.hh"

class MockConnection : public Connection {
public:
  MockConnection(const MockConnection &) = delete;
  MockConnection &operator=(const MockConnection &) = delete;

  ~MockConnection() = default;
  MockConnection();

  bool isConnected() override;
  bool login(std::string name, std::string pass) override;
  std::optional<std::string> registerAccount(std::string name,
                                             std::string pass) override;

  bool isLoggedIn() override;
  bool updateGame(std::string title, std::string description,
                  int price) override; // dodaje też grę jeśli nie ma jej na liście
  bool updateNews(std::string gamename, std::string title,
                  std::string content)
      override; // dodaje też grę jeśli nie ma jej na liście

  bool 
  addSocials(std::string medium,
      std::string link) override; // dodaje też grę jeśli nie ma jej na liście

  bool
  updateSocials(std::string medium,
      std::string link) override; // dodaje też grę jeśli nie ma jej na liście

  std::unique_ptr<UserInfo> getUserInfo() override;

private:
  struct DBDeleter {
    void operator()(sqlite3 *ptr) { sqlite3_close(ptr); }
  };

public:
  using db_ptr = std::unique_ptr<sqlite3, DBDeleter>;

private:
  db_ptr db = nullptr;
  std::optional<UserInfo::ID> userID;
};
