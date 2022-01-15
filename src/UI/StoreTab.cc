
#include "UI/StoreTab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>

#include <sstream>
#include <string>

void StoreTab::onSearchButton(Fl_Widget *, void *v) {
  ((StoreTab *)v)->gameName->value(((StoreTab *)v)->searchInput->value());
  std::string temp = ((StoreTab *)v)->searchInput->value();
  ((StoreTab *)v)->userSearch(temp);
}

void StoreTab::onBuyButton(Fl_Widget *, void *v) {
  // poniżej sprawdzenie czy działa

  fl_message("Game bought");
}

void StoreTab::onBrowserClick(Fl_Widget *, void *v) {
  ((StoreTab *)v)->updateGamesList();
}

void StoreTab::onDlcBrowserClick(Fl_Widget *, void *v) {

  ((StoreTab *)v)
      ->loadDLCData(((StoreTab *)v)->gameList->value(),
                    ((StoreTab *)v)->dlcList->value());
}

void StoreTab::userSearch(std::string value) {
  int i = 0;
  std::vector<GameInfo> tempVect;
  for (auto game : state.getAllGames()) {
    std::string temp = game.getTitle().c_str();
    if (temp.find(value) != std::string::npos) {
      if (i == 0) {
        priceLabel->clear_active();
        priceLabel->value("");
        gameName->clear_active();
        gameName->value("");
        description->clear_active();
        descriptionBuf->text("");
        buyButton->clear_active();

        gamesVect.clear();

        statusLabel->clear_active();
        dlcList->clear();
        dlcList->clear_active();
        gameList->clear();
      }
      gameList->add(game.getTitle().c_str(), (void *)this);
      tempVect.push_back(game);
      i++;
    }
  }
  if (tempVect.size()) {
    gamesVect.clear();
    gamesVect = tempVect;
  } else {
    fl_alert("No game found");
  }
}

void StoreTab::loadDLCData(int gameID, int dlcID) {
  buyButton->set_active();
  DLCInfo temp = gamesVect[gameID - 1].getDLCs()[dlcID - 1];
  priceLabel->value(std::to_string(temp.getPrice()).c_str());
  gameName->value(temp.getTitle().c_str());
}

void StoreTab::updateGameDLCsList(int gameID) {
  dlcList->clear();

  dlcList->clear();
  for (auto gameDLC : state.getConnection().getAllGamesDLCs(gameID)) {
    dlcList->add(gameDLC.getTitle().c_str(), (void *)this);
  }
}

void StoreTab::updateGamesList() {
  int i = gameList->value();
  if (i == 0) {
    priceLabel->clear_active();
    priceLabel->value("");
    gameName->clear_active();
    gameName->value("");
    description->clear_active();
    descriptionBuf->text("");
    buyButton->clear_active();

    statusLabel->clear_active();
    dlcList->clear();
    dlcList->clear_active();

  } else {
    --i;
    auto selectedGame = gamesVect[i];
    priceLabel->set_active();
    priceLabel->value(std::to_string(selectedGame.getPrice()).c_str());
    gameName->set_active();
    gameName->value(selectedGame.getTitle().c_str());
    description->set_active();
    descriptionBuf->text(selectedGame.getDescription().c_str());
    buyButton->set_active();

    updateGameDLCsList(selectedGame.getID());
    statusLabel->set_active();
    dlcList->set_active();

    // temp
    statusLabel->value("temp");
  }
  redraw();
}

void StoreTab::initGamesList() {
  gameList->clear();

  for (auto game : state.getAllGames()) {
    gameList->add(game.getTitle().c_str(), (void *)this);
    gamesVect.push_back(game);
  }

  updateGamesList();
}

StoreTab::StoreTab(State &s) : Tab("Store", s) {
  // dodać załadowanie listy gier oraz zaznaczenie którą grę się posiada a
  // którą nie,
  gameList = new Fl_Hold_Browser(10, 75, 221, 370);
  gameList->callback(onBrowserClick, this);
  // Fl_Browser* o

  searchInput = new Fl_Input(10, 35, 139, 30);
  searchInput->align(Fl_Align(FL_ALIGN_CENTER));
  // Fl_Input* o

  searchButton = new Fl_Button(159, 35, 72, 30, "search"); // Fl_Button* o
  searchButton->callback(onSearchButton, this);

  Fl_Group *o = new Fl_Group(241, 35, 374, 410);
  o->box(FL_DOWN_BOX);
  gameName = new Fl_Output(302, 45, 303, 30, "Name"); // Fl_Output* o

  buyButton = new Fl_Button(533, 85, 72, 30, "Buy");
  // dodać callbacl
  buyButton->callback(onBuyButton, this);
  buyButton->deactivate();
  // Fl_Button* o

  priceLabel = new Fl_Output(436, 85, 56, 30, "PLN");
  priceLabel->align(Fl_Align(FL_ALIGN_RIGHT));
  // Fl_Output* priceLabel

  statusLabel = new Fl_Output(303, 85, 123, 30, "Staus");
  // Fl_Output* statusLabel

  dlcList = new Fl_Hold_Browser(251, 335, 354, 100, "DLC");
  dlcList->align(Fl_Align(FL_ALIGN_TOP));
  dlcList->callback(onDlcBrowserClick, this);
  // Fl_Browser* o

  description = new Fl_Text_Display(251, 125, 354, 178);
  descriptionBuf = new Fl_Text_Buffer;
  description->buffer(descriptionBuf);

  // Fl_Text_Display* description
  o->end();

  // Fl_Group* o

  end();

  initGamesList();
}
