
#pragma once

#include <optional>
#include <string>
#include <vector>
#include "GameInfo.hh"
#include "DLCInfo.hh"


class Connection {
public:
  Connection(const Connection &) = delete;
  Connection &operator=(const Connection &) = delete;

  Connection() = default;

  virtual ~Connection() = default;
  virtual bool isConnected() = 0;
  virtual bool login(std::string name, std::string pass) = 0;
<<<<<<< HEAD

  virtual std::optional<std::string> registerAccount(std::string name,
                                                     std::string pass) = 0;
  virtual bool
  updateLoginInfo(
      std::string name, std::string pass) = 0; // przetestować jeszcze trzeba

  virtual std::vector<GameInfo> getAllGames() = 0;
  virtual std::vector<DLCInfo> getAllDlc(int64_t id) = 0;

  virtual std::vector<GameInfo> getOwnedGames(int64_t userID) = 0;
  virtual std::vector<DLCInfo> getOwnedDlc(int64_t userID, int64_t gameID) = 0;
  virtual DLCInfo getDLCInfo(int64_t DlcID) = 0;
  virtual GameInfo getGameInfo(int64_t gameID) = 0;


=======
>>>>>>> 8ea2ec3e53f493e9c2ff13513af4d4845527ea6c

  virtual std::optional<std::string> registerAccount(std::string name,
                                                     std::string pass) = 0;
};
