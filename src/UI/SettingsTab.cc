
#include "UI/SettingsTab.hh"

#include "FL/fl_ask.H"
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>

void SettingsTab::onUpdateButton(Fl_Widget *, void *v) {
  // test czy działa, potem usunąć
  printf(((SettingsTab *)v)->newNameField->value());

  std::string newLogin = ((SettingsTab *)v)->newNameField->value();
  std::string newPassword = ((SettingsTab *)v)->newPasswordField->value();

  if (!newLogin.empty() && !newPassword.empty()) {
    if (fl_ask("Do you really want to update data?")) {
      // może dodać do connect metode zwracającej info czy jest użytkownik o
      // danym loginie, bo hasło powinno móc się powtarzać
      if (1) {
        // if (connection.updateLogin(newLogin, newPassword)
        fl_message("succes");
      } else {
        //          fl_error("error");
      }
    }
  } else {
    //          fl_error("error");
  }
}

SettingsTab::SettingsTab(State &s) : Tab("Settings", s) {

  newNameField = new Fl_Input(250, 175, 135, 30, "Username");
  Fl_Button *updateButton = new Fl_Button(257, 255, 120, 25, "Update");

  newPasswordField = new Fl_Input(250, 215, 135, 30, "Password");
  newPasswordField->type(5);
  updateButton->callback(onUpdateButton, this);

  end();
}
