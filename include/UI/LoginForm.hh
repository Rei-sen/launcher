
#pragma once

#include <functional>
#include <optional>
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>

#include "Connection.hh"

class LoginForm {
public:
  LoginForm(Connection &con);
  void show();

private:
<<<<<<< HEAD

  static void cb_Login(Fl_Button *, LoginForm *);


=======
>>>>>>> e8cd054f86785f125268187277261f0ecb373539
  Connection &connection;
};
