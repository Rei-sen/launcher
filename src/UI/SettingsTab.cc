
#include "UI/SettingsTab.hh"

#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

SettingsTab::SettingsTab(State &s) : Tab("Settings", s) {
  { new Fl_Input(250, 175, 135, 30, "Username"); } // Fl_Input* o
  { new Fl_Button(280, 255, 72, 25, "Update"); }   // Fl_Button* o
  { new Fl_Input(250, 215, 135, 30, "Password"); } // Fl_Input* o

  end();
}
