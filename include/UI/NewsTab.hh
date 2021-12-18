
#pragma once

#include "UI/Tab.hh"

class NewsTab : public Tab {
public:
  NewsTab(const NewsTab &) = delete;
  NewsTab &operator=(const NewsTab &) = delete;
  virtual ~NewsTab() = default;

  NewsTab(State &s);
};
