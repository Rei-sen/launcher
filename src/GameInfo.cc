
#include "GameInfo.hh"

#include "DLCInfo.hh"

GameInfo::GameInfo(ID id, std::string title, std::string description,
                   double price, std::vector<DLCInfo> dlcs)
    : id(id), title(title), description(description), price(price),
      dlcs(dlcs){};

GameInfo::ID GameInfo::getID() const { return id; }
std::string GameInfo::getTitle() const { return title; }
std::string GameInfo::getDescription() const { return description; }
double GameInfo::getPrice() const { return price; }
std::vector<DLCInfo> GameInfo::getDLCs() const { return dlcs; }
