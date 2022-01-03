
#pragma once

#include "UI/Tab.hh"

#include <FL/Fl_Output.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>

class GameLibTab : public Tab {
public:
  GameLibTab(const GameLibTab &) = delete;
  GameLibTab &operator=(const GameLibTab &) = delete;
  virtual ~GameLibTab() = default;

  GameLibTab(State &s);
  void searchButtonMet();

  void playButtonMet();
  void updateDlcAndNameMet();

  static void playButtonCallback(Fl_Widget *, void *v) {
    ((GameLibTab *)v)->playButtonMet();
  }

    void instalButtonMet();

  static void instalButtonCallback(Fl_Widget *, void *v) {
      ((GameLibTab *)v)->instalButtonMet();
  }

    void uninstallButtonMet();

  static void uninstalButtonCallback(Fl_Widget *, void *v) {
      ((GameLibTab *)v)->uninstallButtonMet();
  }

    static void searchButtonCallback(Fl_Widget *, void *v) {
    ((GameLibTab *)v)->searchButtonMet();
  }

      static void updateDlcAndNameCallback(Fl_Widget *, void *v) {
    ((GameLibTab *)v)->updateDlcAndNameMet();
  }

private:
  Fl_Input *searchInput;
  Fl_Browser *gameList;
// chyba w układzie trzeba coś zmienić
//  Fl_Browser *dlcList;
  Fl_Output *gameName;

  Fl_Button *playButton;
  Fl_Button *uninnstallButton;
  Fl_Button *innstallButton;
  Fl_Table *dlcTab;

  Fl_Button *searchButton;
};
