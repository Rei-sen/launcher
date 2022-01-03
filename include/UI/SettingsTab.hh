
#pragma once

#include "UI/Tab.hh"
#include <FL/Fl.H>
#include <string>
#include <FL/Fl_Input.H>

class SettingsTab : public Tab {
public:
  SettingsTab(const SettingsTab &) = delete;
  SettingsTab &operator=(const SettingsTab &) = delete;
  virtual ~SettingsTab() = default;

  SettingsTab(State &s);


  void updateButtonMet();

  static void updateButtonCallback(Fl_Widget *, void *v) {
    ((SettingsTab *)v)->updateButtonMet();
  }

private:
  Fl_Input *newNameField;
  Fl_Input *newPasswordField;
};
