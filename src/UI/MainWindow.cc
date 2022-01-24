
#include "UI/MainWindow.hh"

#include "UI/GameLibTab.hh"
#include "UI/NewsTab.hh"
#include "UI/PublisherTab.hh"
#include "UI/SettingsTab.hh"
#include "UI/SocialMediaTab.hh"
#include "UI/StoreTab.hh"

void MainWindow::refreshAll() {
    
 
  gameLibTab->initGamesList();
  socialMediaTab->initTab();
  newsTab->initTabData();
  storeTab->initGamesList();
}


void MyTabCallback(Fl_Widget *w, void *_this) {
  Fl_Tabs *tabs = (Fl_Tabs *)w;
  // When tab changed, make sure it has same color as its group
  ((MainWindow *)_this)->refreshAll();
  
}

MainWindow::MainWindow(State &s)
    : Fl_Double_Window(625, 455, "Game launcher") {
  user_data((void *)(this));
  {
    Fl_Tabs *tabs = new Fl_Tabs(0, 0, 625, 455);
    tabs->callback(MyTabCallback, (void *)this);
    {
      storeTab = new StoreTab(s);
      Fl_Group *o = storeTab;
      o->show();
    }                      // StoreTab* o
    { gameLibTab = new GameLibTab(s); } // GameLibTab* o
    socialMediaTab = new SocialMediaTab(s);
    newsTab = new NewsTab(s);
    new SettingsTab(s);
    if (true) // zamienić na state.user.hasPublisherAccess()
    {
      new PublisherTab(s);
    } // PublisherGroup* o
    tabs->end();
  } // Fl_Tabs* o
  end();
}
