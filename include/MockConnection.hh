
#pragma once

#include <sqlite3.h>


#include "Connection.hh"
#include "UserInfo.hh"
#include "News.hh"
#include "SocialMedia.hh"

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
  std::vector<News> getAllNews() override;
  std::vector<SocialMedia> getAllMedias() override;


  std::vector<DLCInfo> getAllGamesDLCs(GameInfo::ID id) override;

  std::unique_ptr<UserInfo> getUserInfo() override;
  std::vector<GameInfo::ID> getOwnedGames() override;
  std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> getOwnedDLCs() override;

  bool updateGameInfo(GameInfo info) override;

  bool updateNewsInfo(News info) override;

  bool updateMediaInfo(SocialMedia info ) override;


  std::optional<std::string> addNewsInfo(GameInfo::ID gid, std::string title,
                                         std::string content) override;
  std::optional<std::string> addMedia(SocialMedia medium) override;

  std::optional<std::string> buyGame(GameInfo::ID id) override;
  std::optional<std::string> buyDLC(GameInfo::ID gameId,
                                    DLCInfo::ID id) override;


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
