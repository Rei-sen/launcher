
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

#include <algorithm>
#include <ranges>
#include <stdexcept>
#include <string>
#include <regex>

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
      newsTree = new Fl_Tree(10, 245, 155, 170); // Fl_Tree* o
      newsTree->root_label("Games");
      newsTree->callback(onNewsTreeSelected, (void *)this);
      { newsTitle = new Fl_Input(230, 245, 360, 30, "title"); } // Fl_Input* o
      {
        newsUpdateAdd = new Fl_Button(500, 410, 90, 25, "Update/Add");
        newsUpdateAdd->callback(onUpdateNews, (void *)this);
      } // Fl_Button* o
      {
        newsContentBuf = new Fl_Text_Buffer;
        newsContent = new Fl_Text_Editor(230, 290, 360, 110, "Content");
        newsContent->buffer(newsContentBuf);
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
        socialsUpdate->callback(onUpdateMedia, (void *)this);

      } // Fl_Button* o
      {
        socialsPlatform = new Fl_Choice(84, 478, 120, 30, "Platform");
        socialsPlatform->down_box(FL_BORDER_BOX);
        socialsPlatform->callback(onMediaChoiceSelected, (void *)this);
      } // Fl_Choice* o
      {
        socialsAddNew =
            new Fl_Button(514, 478, 75, 30, "Add new"); // onUpdateSocialButton
        socialsAddNew->callback(onAddMedia, (void *)this);
      
      }                                                 // Fl_Button* o
      o->end();
    } // Fl_Group* o
    o->end();
  } // Fl_Scroll* o

  initAllGroups();
}

void PublisherTab::initAllGroups() {
  initGameGroup();
  initNewsGroup();
  initMediaGroup();
}

void PublisherTab::initGameGroup() {
  gameBrowser->clear();
  for (auto game : state.getAllGames()) {
    gameBrowser->add(game.getTitle().c_str(), (void *)this);
  }

  updateGameGroup();
}

void PublisherTab::initNewsGroup() {
  auto news = state.getAllNews();
  auto games = state.getAllGames();
  newsTree->clear();
  newsTree->root_label("Games");
  newsTree->select("Games");
  newsTree->callback_item(newsTree->root());

  for (auto game : games) {
    std::string temp = ("/" + game.getTitle());
    newsTree->add(temp.c_str());
  }

  std::for_each(news.begin(), news.end(), [&](News n) {
    auto gamename = std::find_if(games.begin(), games.end(), [&](GameInfo nn) {
      return nn.getID() == n.getGameID();
    });
    std::string temp = ("/" + gamename->getTitle() + "/" + n.getTitle());
    newsTree->add(temp.c_str());
  });
  updateNewsGroup();
  redraw();
}

void PublisherTab::initMediaGroup() {
  std::vector<SocialMedia> medias = state.getAllMedias();
  socialsPlatform->clear();
  int temp = socialsPlatform->value();
  if (temp < 0)
    temp = 0;
  for (SocialMedia m :  medias)
  socialsPlatform->add(m.getName().c_str());
  socialsPlatform->value(temp);
  socialsAddress->value(medias[0].getAddress().c_str());
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

void PublisherTab::updateNewsGroup() {
  auto news = state.getAllNews();
  auto games = state.getAllGames();
  newsTree->root_label("Games");

  if (newsTree->callback_item() == nullptr||newsTree->callback_item()->is_root() ||
      !newsTree->callback_item()) {
    newsTitle->clear_active();
    newsTitle->value("");
    newsContent->clear_active();
    newsContentBuf->text("");
    newsUpdateAdd->clear_active();
    newsUpdateAdd->label("Add/Update");
    callback_news = "";
    callback_game = "";
  } else if (newsTree->callback_item()->parent()->is_root()) {
    newsTitle->set_active();
    newsTitle->value("");
    newsContent->set_active();
    newsContentBuf->text("");
    newsUpdateAdd->set_active();
    newsUpdateAdd->label("Add");
    callback_news = "";
    callback_game = newsTree->callback_item()->label();
    newsUpdateAdd->callback(onAddNews, (void *)this);

  } else { // here get all contents of this stuff
    GameInfo::ID iddd;
    auto ne = std::find_if(games.begin(), games.end(), [&](GameInfo n) {
      std::string temp = newsTree->callback_item()->parent()->label();
      return n.getTitle() == temp;
    });
    if (ne != games.end()) {

      iddd = ne->getID();
      auto ne2 = std::find_if(news.begin(), news.end(), [&](News n) {
        std::string temp = newsTree->callback_item()->label();
        return n.getTitle() == temp && iddd == n.getGameID();
      });

      newsTitle->set_active();
      newsTitle->value(ne2->getTitle().c_str());
      newsContent->set_active();
      newsContentBuf->text(ne2->getContent().c_str());
      newsUpdateAdd->set_active();
      newsUpdateAdd->label("Update");

      callback_news = newsTree->callback_item()->label();
      callback_game = newsTree->callback_item()->parent()->label();
      newsUpdateAdd->callback(onUpdateNews, (void *)this);
    }
  }
  redraw();
}

void PublisherTab::updateMediaGroup() { 
  std::vector<SocialMedia> medias = state.getAllMedias();
  int temp = socialsPlatform->value();
  socialsAddress->value(medias[temp].getAddress().c_str());
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

void PublisherTab::onUpdateNews(Fl_Widget *, void *_this) {
  auto tab = (PublisherTab *)_this;
  auto games = tab->state.getAllGames();
  auto news = tab->state.getAllNews();
  auto callback = tab->newsTree->callback_item();
  std::string check = tab->newsTitle->value();
  if (std::all_of(check.begin(), check.end(), isspace)||check.empty())
    return;

  if (callback == nullptr || callback->parent() == nullptr ||
      callback->parent()->is_root())
    return;

  GameInfo::ID idG;
  News::ID idN;
  std::string temp = tab->callback_game;
  auto ne = std::find_if(games.begin(), games.end(),
                         [&](GameInfo n) { return n.getTitle() == temp; });
  if (ne == games.end())
    return;
  temp = tab->callback_news;
  idG = ne->getID();
  auto ne2 = std::find_if(news.begin(), news.end(), [&](News n) {
    return n.getTitle() == temp && idG == n.getGameID();
  });
  if (ne2 == news.end())
    return;
  idN = ne2->getID();

  News newnews(idN, idG, tab->newsTitle->value(), tab->newsContentBuf->text());

  tab->state.getConnection().updateNewsInfo(newnews);

  tab->state.update();
  tab->initAllGroups();
}

void PublisherTab::onAddNews(Fl_Widget *, void *_this) {
  auto tab = (PublisherTab *)_this;
  auto games = tab->state.getAllGames();
  auto callback = tab->newsTree->callback_item();
  std::string check = tab->newsTitle->value();
  if (std::all_of(check.begin(), check.end(), isspace) || check.empty())
    return;

  if (callback == nullptr || callback->parent() == nullptr )
    return;
  GameInfo::ID idG;
  std::string temp = tab->callback_game;
  auto ne = std::find_if(games.begin(), games.end(),
                         [&](GameInfo n) { return n.getTitle() == temp; });
  if (ne == games.end())
    return;
  idG = ne->getID();


  tab->state.getConnection().addNewsInfo(idG, tab->newsTitle->value(),
                                         tab->newsContentBuf->text());

  tab->state.update();
  tab->initAllGroups();
}

void PublisherTab::onUpdateMedia(Fl_Widget *, void *_this) {
  auto tab = (PublisherTab *)_this;
  auto medias = tab->state.getAllMedias();

  auto socialadress = tab->socialsAddress->value();
  auto socialname = medias[tab->socialsPlatform->value()].getName();

  SocialMedia s(socialname, socialadress);
  tab->state.getConnection().updateMediaInfo(s);

  tab->state.update();
  tab->initAllGroups();
}

void PublisherTab::onAddMedia(Fl_Widget *, void *_this) {
  auto tab = (PublisherTab *)_this;
  std::string socialadress = tab->socialsAddress->value();
  std::string socialname = "";

  int xd = socialadress.find_first_of("//")+2;
  int xe = socialadress.find_first_of("www.") + 4;
  if (xe > xd&&xe<socialadress.length())
    xd = xe;
  if (xd < 0)
    xd = 0;
  socialname = socialadress.substr(xd);
  xe = socialname.find_first_of(".");
  if (xe < 0)
    return;
  socialname = socialname.substr(0, xe);
  //socialname = std::regex_replace(socialadress, urlRe, "$1");


  SocialMedia s(socialname, socialadress);

  tab->state.getConnection().addMedia(s);

  tab->state.update();
  tab->initAllGroups();
}

void PublisherTab::onNewsTreeSelected(Fl_Widget *, void *_this) {
  ((PublisherTab *)_this)->updateNewsGroup();
}

void PublisherTab::onMediaChoiceSelected(Fl_Widget *, void *_this) {
  ((PublisherTab *)_this)->updateMediaGroup();
}


