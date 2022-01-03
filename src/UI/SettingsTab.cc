
#include "UI/SettingsTab.hh"

#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include "FL/fl_ask.H"
#include <FL/Fl_Double_Window.h>

void SettingsTab::updateButtonMet() { 
    // test czy działa, potem usunąć
    printf(newNameField->value()); 

    std::string newLogin = newNameField->value();
    std::string newPassword = newPasswordField->value();

    if (newLogin.length() && newPassword.length()) {
      if (fl_ask("Do you really want to update data?")) {
        // może dodać do connect metode zwracającej info czy jest użytkownik o
        // danym loginie, bo hasło powinno móc się powtarzać
        if (1) {
          //        if (connect.updateLogin(data) &&
          //        connect.updatePassword(data)) {
          //          dodać wiadomość o poprawnej zmianie

        } else {
          //          fl_error("niepoprawne");
        }
      }
    } else {
      //          fl_error("niepoprawne");
    }


}



SettingsTab::SettingsTab(State &s) : Tab("Settings", s) {

    newNameField = new Fl_Input(250, 175, 135, 30, "Username");
    Fl_Button *updateData =
    new Fl_Button(257, 255, 120, 25, "Update");

    newPasswordField = new Fl_Input(250, 215, 135, 30, "Password");
    newPasswordField->type(5);    
    updateData->callback(updateButtonCallback, this);

    end();
}
