
#pragma once

#include <string>
#include <vector>

class Connection {
public:
  Connection(const Connection &) = delete;
  Connection &operator=(const Connection &) = delete;

  Connection() = default;

  virtual ~Connection() = default;
  virtual bool isConnected() = 0;
  virtual bool login(std::string name, std::string pass) = 0;
  virtual bool registerAccount(std::string name, std::string pass) = 0;
  virtual std::vector<std::string> getAllGames()=0;
  virtual std::vector<std::string> getAllDlc() = 0;
  virtual bool updatePassword(std::string pass) =0;
};
