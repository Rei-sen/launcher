
#pragma once

#include <string>
#include <vector>

#include "GameInfo.hh"

class DLCInfo {
public:
  using ID = int64_t;

  DLCInfo() = delete;
  DLCInfo(GameInfo::ID gameID, ID id, std::string title, double price);

  GameInfo::ID getGameID() const;
  ID getID() const;
  std::string getTitle() const;
  double getPrice() const;

private:
  GameInfo::ID gameID;
  ID id;
  std::string title;
  double price;
};
