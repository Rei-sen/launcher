
#pragma once

#include <memory>
#include <optional>
#include <string>

#include "UserInfo.hh"

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

  virtual std::unique_ptr<UserInfo> getUserInfo() = 0;
};
