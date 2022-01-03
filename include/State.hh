
#pragma once

#include <memory>

#include <FL/Fl_Group.H>

#include "Connection.hh"

class State {
public:
  Connection &getConnection();
  void setConnection(std::unique_ptr<Connection> &&Connection);

private:
  std::unique_ptr<Connection> con;
};
