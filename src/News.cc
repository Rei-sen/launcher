
#include "News.hh"

News::News(ID id, GameInfo::ID gameID, std::string title, std::string content)
    : id(id), gameID(gameID), title(title), content(content) {}

News::ID News::getID() const { return id; }
GameInfo::ID News::getGameID() const { return gameID; }
std::string News::getTitle() const { return title; }
std::string News::getContent() const { return content; }
