
#pragma once

#include "Connection.hh"

class MockConnection : public Connection {
public:
  MockConnection(const MockConnection &) = delete;
  MockConnection &operator=(const MockConnection &) = delete;

  ~MockConnection() = default;
  MockConnection() = default;

  bool isConnected() override;
  bool login(std::string name, std::string pass) override;
  bool registerAccount(std::string name, std::string pass) override;
};
