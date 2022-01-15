
#include "UI/GameLibTab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Table.H>
#include <FL/fl_ask.H>

void GameLibTab::onPlayButton(Fl_Widget *, void *v) {
  fl_message("Game launched");
}

void GameLibTab::onInstallButton(Fl_Widget *, void *v) {
  fl_message("Game installed");
  // dodać gdzieś info o tym, że użytkownik ma zainstalowaną grę
}
void GameLibTab::onUninstallButton(Fl_Widget *, void *v) {
  fl_message("Game uninstalled");
  // dodać gdzieś info o tym, że użytkownik odinstalował grę
}
void GameLibTab::onSearchButton(Fl_Widget *, void *v) {
  ((GameLibTab *)v)->gameName->value(((GameLibTab *)v)->searchInput->value());
  std::string temp = ((GameLibTab *)v)->searchInput->value();
  ((GameLibTab *)v)->userSearch(temp);
}

void GameLibTab::onBrowserClick(Fl_Widget *, void *v) {
  printf("lista");
  ((GameLibTab *)v)->updateGamesList();
}

void GameLibTab::onDLCBrowserClick(Fl_Widget *, void *v) {

  // tego ostatecznie ma nie być prawda?
}

// może troszkę myloncje jest tutaj to gameID ale teraz niewiem jak to nazwać
// innaczej
void GameLibTab::updateGameDLCsList(int gameID) {
  dlcList->clear();
  ownedGameDLCsVect.clear();

  GameInfo tempGame = state.getConnection().getAllGames()[gameID - 1];
  std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> tempOwnedDlCs =
      state.getConnection().getOwnedDLCs();

  std::vector<DLCInfo> tempDLCs;
  for (auto ownedProd : tempOwnedDlCs) {
    if (ownedProd.first == gameID) {
      tempDLCs.push_back(tempGame.getDLCs()[ownedProd.second - 1]);
      dlcList->add(
          tempGame.getDLCs()[ownedProd.second - 1].getTitle().c_str());
      ownedGameDLCsVect.push_back(tempGame.getDLCs()[ownedProd.second - 1]);
    }
  }
}

void GameLibTab::userSearch(std::string value) {
  int i = 0;

  std::vector<GameInfo> tempOwnedGames;
  std::vector<GameInfo::ID> ownedID = state.getConnection().getOwnedGames();
  gameList->clear();
  for (auto game : state.getConnection().getAllGames()) {
    for (auto owned : ownedID) {
      if (owned == game.getID()) {
        tempOwnedGames.push_back(game);
      }
    }
  }

  std::vector<GameInfo> tempVect;
  for (auto game : tempOwnedGames) {
    std::string temp = game.getTitle().c_str();
    if (temp.find(value) != std::string::npos) {
      if (i == 0) {
        gameName->clear_active();
        gameName->value("");

        dlcList->clear();
        dlcList->clear_active();
        gameList->clear();
        ownedGameDLCsVect.clear();
        ownedGamesVect.clear();
      }
      gameList->add(game.getTitle().c_str(), (void *)this);
      tempVect.push_back(game);
      i++;
    }
  }
  if (tempVect.size()) {
    ownedGamesVect.clear();
    ownedGamesVect = tempVect;
  } else {
    fl_alert("No game found");
  }
}

void GameLibTab::initGamesList() {

  std::vector<GameInfo::ID> ownedID = state.getConnection().getOwnedGames();
  gameList->clear();
  for (auto game : state.getConnection().getAllGames()) {
    for (auto owned : ownedID) {
      if (owned == game.getID()) {
        gameList->add(game.getTitle().c_str(), (void *)this);
        ownedGamesVect.push_back(game);
      }
    }
  }
  updateGamesList();
}

void GameLibTab::updateGamesList() {
  int i = gameList->value();
  if (i == 0) {
    gameName->clear_active();
    gameName->value("");
    playButton->clear_active();
    uninstallButton->clear_active();
    installButton->clear_active();
    dlcList->clear();
    ownedGameDLCsVect.clear();

  } else {
    --i;
    auto selectedGame = ownedGamesVect[i];
    gameName->set_active();
    gameName->value(selectedGame.getTitle().c_str());
    updateGameDLCsList(selectedGame.getID());

    playButton->set_active();
    uninstallButton->set_active();
    installButton->set_active();
  }

  redraw();
}

GameLibTab::GameLibTab(State &s) : Tab("Game library", s) {

  gameList = new Fl_Hold_Browser(10, 75, 221, 370);
  gameList->callback(onBrowserClick, this);

  searchInput = new Fl_Input(10, 35, 139, 30);
  searchInput->align(Fl_Align(FL_ALIGN_CENTER));

  searchButton = new Fl_Button(159, 35, 72, 30, "search");
  searchButton->callback(onSearchButton, this);

  Fl_Group *o = new Fl_Group(241, 35, 374, 410);
  o->box(FL_DOWN_BOX);
  gameName = new Fl_Output(302, 45, 303, 30, "Name");

  playButton = new Fl_Button(533, 85, 72, 30, "Play");
  playButton->deactivate();
  playButton->callback(onPlayButton, this);

  installButton = new Fl_Button(451, 85, 72, 30, "Install");
  installButton->callback(onInstallButton, this);

  installButton->deactivate();

  uninstallButton = new Fl_Button(369, 85, 72, 30, "Uninstall");
  uninstallButton->callback(onUninstallButton, this);
  uninstallButton->deactivate();

  dlcList = new Fl_Hold_Browser(251, 150, 354, 285, "DLC");
  dlcList->callback(onDLCBrowserClick, this);

  o->end();
  end();

  initGamesList();
}
