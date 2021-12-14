
#pragma once

#include "UI/Tab.hh"

class GameLibTab : public Tab {
public:
  GameLibTab(const GameLibTab &) = delete;
  GameLibTab &operator=(const GameLibTab &) = delete;
  virtual ~GameLibTab() = default;

  GameLibTab(State &s);
};
