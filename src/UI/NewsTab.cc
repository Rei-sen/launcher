
#include "UI/NewsTab.hh"


void NewsTab::initTabData() { 
  newsTree->clear();
  titleField->clear_active();
  contentField->clear_active();
  
  newsVector = state.getConnection().getAllNews();
  std::vector<GameInfo> temp = state.getConnection().getAllGames();

  std::string gameNews;
  for (auto curentNews : newsVector) {
    gameNews = temp[curentNews.getGameID()-1].getTitle() + "/";
    gameNews += curentNews.getTitle();
    newsTree->add(gameNews.c_str());
  }

  updateTabData();
}

void NewsTab::updateTabData() {
  std::string tempLabel;
    std::vector<GameInfo> temp = state.getConnection().getAllGames();

  Fl_Tree_Item *i = newsTree->first_selected_item();
  if (i != nullptr) {
    tempLabel = i->label();
    for (auto newsElement : newsVector) {
        if (newsElement.getTitle() == tempLabel) {
          titleField->set_active();
          contentField->set_active();
          newsTitleBuf->text(tempLabel.c_str());
          newsContentBuf->text(newsElement.getContent().c_str());
        }
    }
  } else {
    newsTitleBuf->text("");
    newsContentBuf->text("");
    titleField->clear_active();
    contentField->clear_active();
  }
  newsTree->root_label("News list");
}



void NewsTab::onNewsTreeSelected(Fl_Widget *, void *_this) {
  ((NewsTab *)_this)->updateTabData();
}


NewsTab::NewsTab(State &s) : Tab("News", s) {
   newsTree = new Fl_Tree(10, 35, 221, 410);   // Fl_Tree* o
  newsTree->callback(onNewsTreeSelected, (void *)this);

  newsTitleBuf = new Fl_Text_Buffer; 
  titleField = new Fl_Text_Display(241, 35, 374, 30);  // Fl_Text_Display* o
  titleField->buffer(newsTitleBuf);

  newsContentBuf = new Fl_Text_Buffer; 
  contentField = new Fl_Text_Display(241, 75, 374, 370);  // Fl_Text_Display* o
  contentField->buffer(newsContentBuf);

  initTabData();
  end();
}
