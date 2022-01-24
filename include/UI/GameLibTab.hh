#pragma once

#include "UI/Tab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Text_Display.H>

#include <FL/Fl_Hold_Browser.H>

class GameLibTab : public Tab {
public:
  GameLibTab(const GameLibTab &) = delete;
  GameLibTab &operator=(const GameLibTab &) = delete;
  virtual ~GameLibTab() = default;

  GameLibTab(State &s);
  static void onPlayButton(Fl_Widget *, void *v);
  static void onInstallButton(Fl_Widget *, void *v);
  static void onUninstallButton(Fl_Widget *, void *v);
  static void onSearchButton(Fl_Widget *, void *v);
  static void onBrowserClick(Fl_Widget *, void *v);
  static void onDLCBrowserClick(Fl_Widget *, void *v);

  void initGamesList();


private:
  void updateGamesList();
  void updateGameDLCsList(int gameID);
  void userSearch(std::string value);

  std::vector<GameInfo> shownGames;
  std::vector<DLCInfo> ownedGameDLCsVect;

  Fl_Input *searchInput;
  Fl_Hold_Browser *gameList;
  // chyba w układzie trzeba coś zmienić
  //  Fl_Browser *dlcList;
  Fl_Output *gameName;

  Fl_Button *playButton;
  Fl_Button *uninstallButton;
  Fl_Button *installButton;
  Fl_Hold_Browser *dlcList;

  Fl_Button *searchButton;
};