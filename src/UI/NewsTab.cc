
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

    /*
    if (gamesWithNewsVector.size()) {
      bool alreadyAdded = false;
      for (auto gameToAdd : gamesWithNewsVector) {
        if (gameToAdd.getID() == curentNews.getID()) {
          alreadyAdded = true;
          break;
        }
      }
      if (!alreadyAdded) {
        gamesWithNewsVector.push_back(temp[curentNews.getGameID() - 1]);
      }
    } else {
      gamesWithNewsVector.push_back(temp[curentNews.getGameID()-1]);
    }
    */

    // to poniżej do testów jest 
    /*
    gameNews += "a";
    newsTree->add(gameNews.c_str());
    std::string test = "asdwad/asd";
    newsTree->add(test.c_str());
    gameNews += "b";
        newsTree->add(gameNews.c_str());
    */

  }

  updateTabData();
}

void NewsTab::updateTabData() {
//	int i = newsTree->da
  std::string tempLabel;
    std::vector<GameInfo> temp = state.getConnection().getAllGames();
  /*
  for (Fl_Tree_Item *item = newsTree->first(); item;
       item = newsTree->next(item)) {
    printf("Item: %s\n", item->label());
  }
    */

  Fl_Tree_Item *i = newsTree->first_selected_item();
  if (i != nullptr) {
//    printf("wybrany ");
    tempLabel = i->label();
//    printf(i->label());
//   printf("\n");
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

//  newsVector = state.getConnection().getAllNews();
  
//  printf(newsVector[0].getTitle().c_str());
//
  initTabData();
  end();
}
