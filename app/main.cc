
#include <iostream>

#if defined(WIN32) || defined(_WIN32) ||                                      \
    defined(__WIN32) && !defined(__CYGWIN__)
#include <filesystem>
#endif

#include <sqlite3.h>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>

#include "MockConnection.hh"
#include "UI/LoginForm.hh"
#include "UI/MainWindow.hh"

int main(int argc, char **argv) {
#if defined(WIN32) || defined(_WIN32) ||                                      \
    defined(__WIN32) && !defined(__CYGWIN__)
  std::filesystem::current_path("../../../");
#endif
  /* to co niżej do poprawy */
  std::unique_ptr<Connection> connection = std::make_unique<MockConnection>();
  LoginForm f(*connection);
  f.show();

  if (!connection->isLoggedIn())
    return 0;

  State state(std::move(connection));

  MainWindow w(state);
  w.show();

  return Fl::run();
}
