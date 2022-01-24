
#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>

#include "UI/GameLibTab.hh"
#include "UI/PublisherTab.hh"
#include "UI/StoreTab.hh"

#include "UI/SocialMediaTab.hh"
#include "UI/NewsTab.hh"


class MainWindow : public Fl_Double_Window {
public:
  MainWindow(State &s);
  virtual ~MainWindow() = default;

  void refreshAll();

private:
  GameLibTab *gameLibTab;
  SocialMediaTab *socialMediaTab;
  NewsTab *newsTab;
  StoreTab *storeTab;

//  void MyTabCallback(Fl_Widget *w, void *);

};
