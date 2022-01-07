
#pragma once

#include <string>
#include <vector>

class DLCInfo {
public:
  DLCInfo() = delete;
  DLCInfo(int gameID, int id, std::string title, double price);

  int getGameID();
  int getID();
  std::string getTitle();
  double getPrice();

private:
  int gameID;
  int id;
  std::string title;
  double price;
};
