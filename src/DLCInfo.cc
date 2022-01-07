
#include "DLCInfo.hh"

DLCInfo::DLCInfo(int gameID, int id, std::string title, double price)
    : gameID(gameID), id(id), title(title), price(price) {}

int DLCInfo::getGameID() { return gameID; }
int DLCInfo::getID() { return id; }
std::string DLCInfo::getTitle() { return title; }
double DLCInfo::getPrice() { return price; }
