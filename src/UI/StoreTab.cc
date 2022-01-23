
#include "UI/StoreTab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>

#include <iostream>
#include <ranges>
#include <sstream>
#include <string>

class DLCTable : public Fl_Table {
public:
  DLCTable(int x, int y, int w, int h, const char *l = 0)
      : Fl_Table(x, y, w, h, l) {
    col_resize(1);
    col_header_height(25);
    row_resize(0);
    row_header_width(80);
    cols(3);
    end();
  }

  void set(std::vector<DLCInfo> dlcs,
           std::vector<std::pair<GameInfo::ID, DLCInfo::ID>> owned,
           void (*callback)(Fl_Widget *, void *),
           std::vector<std::pair<unsigned, void *>> &argList) {
    clear();
    rows(dlcs.size());
    cols(3);

    begin();
    for (unsigned i = 0; i < dlcs.size(); ++i) {
      int x, y, w, h;

      find_cell(CONTEXT_TABLE, i, 0, x, y, w, h);
      auto title = new Fl_Output(x, y, w, h);
      title->value(dlcs[i].getTitle().c_str());
      find_cell(CONTEXT_TABLE, i, 1, x, y, w, h);
      auto price = new Fl_Output(x, y, w, h);
      price->value(std::to_string(dlcs[i].getPrice()).c_str());
      find_cell(CONTEXT_TABLE, i, 2, x, y, w, h);

      auto btn = new Fl_Button(x, y, w, h);
      if (std::find_if(owned.begin(), owned.end(), [dlcs, i](auto pair) {
            return dlcs[i].getGameID() == std::get<0>(pair) &&
                   dlcs[i].getID() == std::get<1>(pair);
          }) == owned.end()) {
        btn->label("Buy");
        btn->set_active();
        btn->callback(callback, (void *)&argList[i]);
      } else {
        btn->label("Owned");
        btn->clear_active();
      }
    }
    end();
    redraw();
  }
};

void StoreTab::onSearchButton(Fl_Widget *, void *_this) {
  auto tab = (StoreTab *)_this;

  tab->shownGames.clear();
  tab->gameList->clear();

  for (auto game :
       tab->state.getAllGames() | std::views::filter([tab](auto game) {
         return game.getTitle().find(tab->searchInput->value()) !=
                std::string::npos;
       })) {
    tab->gameList->add(game.getTitle().c_str(), _this);
    tab->shownGames.push_back(game);
  }

  tab->updateGamesList();
}

void StoreTab::onBuyButton(Fl_Widget *, void *_this) {
  // poniżej sprawdzenie czy działa
  auto tab = ((StoreTab *)_this);
  int i = tab->gameList->value();
  if (i != 0) {

    --i;

    auto result = tab->state.getConnection().buyGame(
        tab->state.getAllGames()[i].getID());
    fl_message("Result: %s", result.value_or("Success").c_str());

    tab->state.update();
    tab->initGamesList();
  } else
    fl_message("Error");
}

void StoreTab::onBrowserClick(Fl_Widget *, void *v) {
  ((StoreTab *)v)->updateGamesList();
}

void StoreTab::onDlcBrowserClick(Fl_Widget *, void *arg) {
  auto argument = (std::pair<unsigned, void *> *)arg;
  auto tab = (StoreTab *)std::get<1>(*argument);
  unsigned i = std::get<0>(*argument);

  auto dlc = tab->shownDLCs[i];

  auto result =
      tab->state.getConnection().buyDLC(dlc.getGameID(), dlc.getID());

  fl_message("Result: %s", result.value_or("Success").c_str());
  tab->state.update();
  tab->initGamesList();
  std::cout << i << std::endl;
}

void StoreTab::loadDLCData(int gameID, int dlcID) {
  buyButton->set_active();
  DLCInfo temp = shownGames[gameID - 1].getDLCs()[dlcID - 1];
  priceLabel->value(std::to_string(temp.getPrice()).c_str());
  gameName->value(temp.getTitle().c_str());
}

void StoreTab::updateGameDLCsList(GameInfo game) {
  dlcList->clear();
  tableArgs.clear();
  shownDLCs.clear();
  auto dlcs = game.getDLCs();
  auto ownedDlcs = state.getUser().getOwnedDLCs();

  unsigned i = 0;
  for (auto dlc : dlcs | std::views::filter([game](auto d) {
                    return game.getID() == d.getGameID();
                  })) {
    shownDLCs.push_back(dlc);
    tableArgs.push_back(std::make_pair(i++, this));
  }
  dlcList->set(shownDLCs, ownedDlcs, onDlcBrowserClick, tableArgs);
  redraw();
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
    auto selectedGame = shownGames[i];
    priceLabel->set_active();
    priceLabel->value(std::to_string(selectedGame.getPrice()).c_str());
    gameName->set_active();
    gameName->value(selectedGame.getTitle().c_str());
    description->set_active();
    descriptionBuf->text(selectedGame.getDescription().c_str());

    statusLabel->set_active();
    auto ownedGames = state.getUser().getOwnedGames();
    if (std::find(ownedGames.begin(), ownedGames.end(),
                  selectedGame.getID()) == ownedGames.end()) {
      statusLabel->value("Not owned");
      buyButton->set_active();
    } else {
      statusLabel->value("Owned");
      buyButton->clear_active();
    }

    dlcList->set_active();
    updateGameDLCsList(selectedGame);
  }
  redraw();
}

void StoreTab::initGamesList() {

  gameList->clear();
  shownGames.clear();
  shownDLCs.clear();

  for (auto game : state.getAllGames()) {
    gameList->add(game.getTitle().c_str(), (void *)this);
    shownGames.push_back(game);
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

  dlcList = new DLCTable(251, 335, 354, 100, "DLC");
  dlcList->align(Fl_Align(FL_ALIGN_TOP));
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
