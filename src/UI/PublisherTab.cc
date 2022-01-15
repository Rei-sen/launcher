
#include "UI/PublisherTab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Tree.H>
#include <FL/fl_ask.H>

#include <stdexcept>

PublisherTab::PublisherTab(State &s) : Tab("Publisher", s) {

  {
    Fl_Scroll *o = new Fl_Scroll(0, 25, 625, 430);
    o->type(2);
    {
      Fl_Group *o = new Fl_Group(10, 65, 590, 135, "Games");
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));

      gameBrowser = new Fl_Hold_Browser(10, 70, 155, 125);
      gameBrowser->callback(onGameBrowserSelected, (void *)this);

      gameName = new Fl_Input(210, 70, 140, 30, "Name");

      gamePrice = new Fl_Float_Input(210, 110, 140, 30, "Price");
      gamePrice->type(1);

      gameDescriptionBuf = new Fl_Text_Buffer;
      gameDescription = new Fl_Text_Editor(360, 70, 230, 122, "Description");
      gameDescription->buffer(gameDescriptionBuf);

      updateGameButton = new Fl_Button(278, 172, 72, 20, "Update");
      updateGameButton->callback(onUpdateGame, (void *)this);
      o->end();
    } // Fl_Group* o
    {
      Fl_Group *o = new Fl_Group(10, 240, 595, 205, "News");
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { new Fl_Tree(10, 245, 155, 170); }                       // Fl_Tree* o
      { newsTitle = new Fl_Input(230, 245, 360, 30, "title"); } // Fl_Input* o
      {
        newsUpdateAdd = new Fl_Button(500, 410, 90, 25, "Update/Add");

      } // Fl_Button* o
      {
        newsContent = new Fl_Text_Editor(230, 290, 360, 110, "Content");
        o->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Text_Editor* o
      o->end();
    } // Fl_Group* o
    {
      Fl_Group *o = new Fl_Group(10, 470, 590, 46, "Social media");
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      {
        socialsAddress = new Fl_Input(272, 478, 153, 30, "Address");
      } // Fl_Input* o
      {
        socialsUpdate = new Fl_Button(435, 478, 69, 30, "Update");

      } // Fl_Button* o
      {
        socialsPlatform = new Fl_Choice(84, 478, 120, 30, "Platform");
        socialsPlatform->down_box(FL_BORDER_BOX);
      } // Fl_Choice* o
      {
        socialsAddNew =
            new Fl_Button(514, 478, 75, 30, "Add new"); // onUpdateSocialButton
      }                                                 // Fl_Button* o
      o->end();
    } // Fl_Group* o
    o->end();
  } // Fl_Scroll* o

  initAllGroups();
}

void PublisherTab::initAllGroups() { initGameGroup(); }

void PublisherTab::initGameGroup() {
  gameBrowser->clear();
  for (auto game : state.getAllGames()) {
    gameBrowser->add(game.getTitle().c_str(), (void *)this);
  }

  updateGameGroup();
}

void PublisherTab::updateGameGroup() {
  int i = gameBrowser->value();
  if (i == 0) {
    gamePrice->clear_active();
    gamePrice->value("");
    gameName->clear_active();
    gameName->value("");
    gameDescription->clear_active();
    gameDescriptionBuf->text("");
    updateGameButton->clear_active();
  } else {
    --i;
    auto selectedGame = state.getAllGames()[i];
    gamePrice->set_active();
    gamePrice->value(std::to_string(selectedGame.getPrice()).c_str());
    gameName->set_active();
    gameName->value(selectedGame.getTitle().c_str());
    gameDescription->set_active();
    gameDescriptionBuf->text(selectedGame.getDescription().c_str());
    updateGameButton->set_active();
  }

  redraw();
}

void PublisherTab::onGameBrowserSelected(Fl_Widget *, void *_this) {
  ((PublisherTab *)_this)->updateGameGroup();
}

void PublisherTab::onUpdateGame(Fl_Widget *, void *_this) {
  auto tab = (PublisherTab *)_this;
  auto oldInfo = tab->state.getAllGames()[tab->gameBrowser->value() - 1];

  double newPrice;

  try {
    newPrice = std::stod(tab->gamePrice->value());
  } catch (std::invalid_argument &) {
    fl_message("invalid number");
    return;
  }

  GameInfo newInfo(oldInfo.getID(), tab->gameName->value(),
                   tab->gameDescriptionBuf->text(), newPrice,
                   oldInfo.getDLCs());

  tab->state.getConnection().updateGameInfo(newInfo);

  tab->state.update();
  tab->initAllGroups();
}
