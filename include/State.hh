
#pragma once

#include <FL/Fl_Group.H>

#include "Connection.hh"

class State {
public:
  Connection &getConnection();
  void setConnection(Connection);

private:
  Connection con;
};
