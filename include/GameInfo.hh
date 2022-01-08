
#pragma once

#include <string>
#include <vector>

class DLCInfo;

class GameInfo {
public:
  using ID = int64_t;

  GameInfo() = delete;
  GameInfo(ID id, std::string title, std::string description, double price,
           std::vector<DLCInfo> dlcs);

  ID getID() const;
  std::string getTitle() const;
  std::string getDescription() const;
  double getPrice() const;
  std::vector<DLCInfo> getDLCs() const;

private:
  ID id;
  std::string title;
  std::string description;
  double price;
  std::vector<DLCInfo> dlcs;
};
