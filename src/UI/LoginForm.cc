
#include "UI/LoginForm.hh"
#include "FL/fl_ask.H"

LoginForm::LoginForm(Connection &con) : connection(con) {}

void LoginForm::show() {
  Fl_Double_Window *win = new Fl_Double_Window(285, 130, "Login");
  win->user_data((void *)(this));

  Fl_Input *loginInput = new Fl_Input(80, 10, 190, 30, "Username");

  Fl_Input *passwordInput = new Fl_Input(80, 50, 190, 30, "Password");
  passwordInput->type(5);

  Fl_Button *loginButton = new Fl_Button(198, 90, 72, 25, "Login");
  Fl_Button *registerButton = new Fl_Button(116, 90, 72, 25, "Register");
  Fl_Button *cancelButton = new Fl_Button(34, 90, 72, 25, "Cancel");
  win->set_modal();
  win->end();
  win->show();

  while (win->shown()) {
    Fl::wait();
    Fl_Widget *o;

    while ((o = Fl::readqueue())) {
      if (cancelButton == o) {
        win->hide();
      } else if (registerButton == o) {

        auto result = connection.registerAccount(loginInput->value(),
                                                 passwordInput->value());
        if (result.has_value())
          fl_alert("Error: %s", result.value().c_str());
        else
          fl_message("Success");

      } else if (loginButton == o) {
        if (connection.login(loginInput->value(), passwordInput->value())) {
          win->hide();
        } else {
          fl_alert("Invalid login or password");
        }
      }
    }
  }
}
