
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
  bool isLoggedIn() override;
  std::optional<std::string> registerAccount(std::string name,
                                             std::string pass) override;

  std::vector<GameInfo> getAllGames() override;
  std::vector<DLCInfo> getAllGamesDLCs(GameInfo::ID id) override;

  std::unique_ptr<UserInfo> getUserInfo() override;
  std::vector<GameInfo::ID> getOwnedGames() override;
  std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> getOwnedDLCs() override;

  bool updateGameInfo(GameInfo info) override;

  std::vector<News> getAllNews() override;

  //
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
