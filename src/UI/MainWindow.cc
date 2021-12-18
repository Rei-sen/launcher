
#include "UI/MainWindow.hh"

#include "UI/GameLibTab.hh"
#include "UI/NewsTab.hh"
#include "UI/PublisherTab.hh"
#include "UI/SettingsTab.hh"
#include "UI/SocialMediaTab.hh"
#include "UI/StoreTab.hh"

MainWindow::MainWindow(State &s)
    : Fl_Double_Window(625, 455, "Game launcher") {
  user_data((void *)(this));
  {
    Fl_Tabs *tabs = new Fl_Tabs(0, 0, 625, 455);
    {
      Fl_Group *o = new StoreTab(s);
      o->show();
    }                      // StoreTab* o
    { new GameLibTab(s); } // GameLibTab* o
    new SocialMediaTab(s);
    new NewsTab(s);
    new SettingsTab(s);
    if (true) // zamienić na state.user.hasPublisherAccess()
    {
      new PublisherTab(s);
    } // PublisherGroup* o
    tabs->end();
  } // Fl_Tabs* o
  end();
}
