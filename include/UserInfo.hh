
#pragma once

#include <cstdint>
#include <vector>

#include "DLCInfo.hh"
#include "GameInfo.hh"

class UserInfo {
public:
  using ID = int64_t;

  UserInfo() = delete;
  UserInfo(std::vector<GameInfo::ID> ownedGames,
           std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> ownedDLCs);

  virtual bool hasPublisherAccess() const;

private:
  std::vector<GameInfo::ID> ownedGames;
  std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> ownedDLCs;
};
