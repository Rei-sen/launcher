
#pragma once

#include <memory>

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

  bool updateGame(std::string title, std::string description,
                  int price); // dodaje też grę jeśli nie ma jej na liście
  bool
  updateNews(std::string gametitle, std::string title,
             std::string content); // dodaje też grę jeśli nie ma jej na liście
  bool
  updateSocials(std::string medium,
                std::string link); // dodaje też grę jeśli nie ma jej na liście

  struct DBDeleter {
    void operator()(sqlite3 *ptr) { sqlite3_close(ptr); }
  };

  using db_ptr = std::unique_ptr<sqlite3, DBDeleter>;

private:
  db_ptr db = nullptr;
  std::optional<UserInfo::ID> userID;
};
