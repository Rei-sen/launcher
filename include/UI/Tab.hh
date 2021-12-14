
#pragma once

#include <string>

#include <FL/Fl_Group.H>

#include "State.hh"

class Tab : public Fl_Group {
public:
  Tab() = delete;
  Tab(const Tab &) = delete;
  Tab &operator=(const Tab &) = delete;
  virtual ~Tab() = default;

protected:
  Tab(const char *name, State &s);

  State &state;
};
