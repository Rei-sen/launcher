
#pragma once

#include "UI/Tab.hh"

class SettingsTab : public Tab {
public:
  SettingsTab(const SettingsTab &) = delete;
  SettingsTab &operator=(const SettingsTab &) = delete;
  virtual ~SettingsTab() = default;

  SettingsTab(State &s);
};
