#pragma once

#include <string>

#include "GameInfo.hh"

class News {
public:
  using ID = int64_t;

  News() = delete;
  News(ID id, GameInfo::ID gameID, std::string title, std::string content);

  ID getID() const;
  GameInfo::ID getGameID() const;
  std::string getTitle() const;
  std::string getContent() const;

private:
  ID id;
  GameInfo::ID gameID;
  std::string title;
  std::string content;
};
