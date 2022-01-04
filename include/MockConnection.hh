
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

  bool updateGame(std::string title,std::string description,int price); //dodaje też grę jeśli nie ma jej na liście
  bool updateNews(std::string gametitle, std::string title, std::string content); //dodaje też grę jeśli nie ma jej na liście
  bool updateSocials(std::string medium, std::string link); //dodaje też grę jeśli nie ma jej na liście

};
