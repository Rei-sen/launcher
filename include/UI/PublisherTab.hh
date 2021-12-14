
#pragma once

#include <UI/Tab.hh>

class PublisherTab : public Tab {
public:
  PublisherTab(const PublisherTab &) = delete;
  PublisherTab &operator=(const PublisherTab &) = delete;
  virtual ~PublisherTab() = default;

  PublisherTab(State &s);
};
