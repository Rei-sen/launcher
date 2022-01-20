
#pragma once

#include <memory>
#include <optional>
#include <string>

#include "UserInfo.hh"
#include "News.hh"

class Connection {
public:
  Connection(const Connection &) = delete;
  Connection &operator=(const Connection &) = delete;

  Connection() = default;

  virtual ~Connection() = default;
  virtual bool isConnected() = 0;
  virtual bool login(std::string name, std::string pass) = 0;
  virtual bool isLoggedIn() = 0;

  virtual std::optional<std::string> registerAccount(std::string name,
                                                     std::string pass) = 0;

  virtual std::vector<GameInfo> getAllGames() = 0;
  virtual std::vector<News> getAllNews() = 0;
  // zwraca wszystkie dlc dla danej gry
  virtual std::vector<DLCInfo> getAllGamesDLCs(GameInfo::ID id) = 0;

  virtual std::unique_ptr<UserInfo> getUserInfo() = 0;
  virtual std::vector<GameInfo::ID> getOwnedGames() = 0;
  virtual std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> getOwnedDLCs() = 0;

  virtual bool updateGameInfo(GameInfo info) = 0;

  virtual bool updateNewsInfo(News info) = 0;

  virtual std::optional<std::string> buyGame(GameInfo::ID id) = 0;
  virtual std::optional<std::string> buyDLC(GameInfo::ID gameId,
                                            DLCInfo::ID id) = 0;
};
