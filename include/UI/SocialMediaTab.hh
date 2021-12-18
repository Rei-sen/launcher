
#pragma once

#include "UI/Tab.hh"

class SocialMediaTab : public Tab {
public:
  SocialMediaTab(const SocialMediaTab &) = delete;
  SocialMediaTab &operator=(const SocialMediaTab &) = delete;
  virtual ~SocialMediaTab() = default;

  SocialMediaTab(State &s);
};
