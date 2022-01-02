
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


  while (true) {
    Fl::wait();
    Fl_Widget *o;

    while ((o = Fl::readqueue())) {
      if (cancelButton == o) {
        // zamiast tego ni¿ej potem dodaæ wy³¹czanie aplikacji
        win->hide();
        return;
      } else if (registerButton == o) {
        // obecnie 1 bo nie ma jeszcze metody z klasy connection
        if (1) {
//        if (!(connection.login(userName->value(),
//        password->value()))) {
//          std::string uName = loginInput->value();
//          std::string uPass = passwordInput->value();
//        obecnie 1 bo nie ma jeszcze metody z klasy connection
          if (1) {
//        if (uName.length() && uPass.length() &&
//              connection.register(uName, uPass)) {
//          dodaæ przekazanie informacji o tym który u¿ytkownik jest
//          zalogowany
            win->hide();
            return;
          } else {
            //          fl_error("niepoprawne");
          }
        } else {
          //          fl_error("niepoprawne");
        }

      } else if (loginButton == o) {
        // obecnie 1 bo nie ma jeszcze metody z klasy connection
        if (1) {
          // if ((connection.login(userName->value(), password->value()))) {
          // dodaæ przekazanie informacji o tym który u¿ytkownik jest
          // zalogowany
          win->hide();
          return;
        } else {
          //  fl_error("niepoprawne");
        }
      }
    }
  }
}
