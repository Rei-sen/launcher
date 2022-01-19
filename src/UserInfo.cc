
#include "UserInfo.hh"

UserInfo::UserInfo(std::vector<GameInfo::ID> ownedGames,
                   std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> ownedDLCs,
                   ID userID)
    : ownedGames(ownedGames), ownedDLCs(ownedDLCs), id(userID) {}

bool UserInfo::hasPublisherAccess() const { return false; }

std::vector<GameInfo::ID> UserInfo::getOwnedGames() { return ownedGames; }
