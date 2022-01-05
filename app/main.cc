
#include <iostream>

#include <sqlite3.h>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>

#include "MockConnection.hh"
#include "UI/LoginForm.hh"
#include "UI/MainWindow.hh"

int main(int argc, char **argv) {
  /* to co niżej do poprawy */
  MockConnection c;
  LoginForm f(c);
  f.show();

  State state;

  MainWindow w(state);
  w.show();

  return Fl::run();
}
