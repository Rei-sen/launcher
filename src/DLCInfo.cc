
#include "DLCInfo.hh"

DLCInfo::DLCInfo(GameInfo::ID gameID, ID id, std::string title, double price)
    : gameID(gameID), id(id), title(title), price(price) {}

GameInfo::ID DLCInfo::getGameID() const { return gameID; }
DLCInfo::ID DLCInfo::getID() const { return id; }
std::string DLCInfo::getTitle() const { return title; }
double DLCInfo::getPrice() const { return price; }
