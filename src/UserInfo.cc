
#include "UserInfo.hh"

UserInfo::UserInfo(std::vector<GameInfo::ID> ownedGames,
                   std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> ownedDLCs)
    : ownedGames(ownedGames), ownedDLCs(ownedDLCs) {}

bool UserInfo::hasPublisherAccess() const { return false; }
