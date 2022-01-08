
#pragma once

#include <sqlite3.h>
#include <vector>

#include "Connection.hh"
#include "UserInfo.hh"



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
                  int price); // dodaje też grę jeśli nie ma jej na liście
  bool
  updateNews(std::string gametitle, std::string title,
             std::string content); // dodaje też grę jeśli nie ma jej na liście
  bool
  updateSocials(std::string medium,
                std::string link); // dodaje też grę jeśli nie ma jej na liście

  std::unique_ptr<UserInfo> getUserInfo() override;

private:
  struct DBDeleter {
    void operator()(sqlite3 *ptr) { sqlite3_close(ptr); }
  };

public:
  using db_ptr = std::unique_ptr<sqlite3, DBDeleter>;

    bool
  updateLoginInfo(std::string name,
                  std::string pass)
      override; // przetestować jeszcze trzeba
  std::vector<GameInfo> getAllGames() override;

  std::vector<DLCInfo> getGamesAllDLCs(int64_t id) override;

  std::vector<GameInfo> getOwnedGames(int64_t userID) override;
  std::vector<DLCInfo> getOwnedDlc(int64_t userID, int64_t gameID) override;
  DLCInfo getDLCInfo(int64_t DlcID) override;
  GameInfo getGameInfo(int64_t gameID) override;

private:
  db_ptr db = nullptr;
  std::optional<UserInfo::ID> userID;
};
