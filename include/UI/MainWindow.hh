
#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>

#include "UI/GameLibTab.hh"
#include "UI/PublisherTab.hh"
#include "UI/StoreTab.hh"

class MainWindow : public Fl_Double_Window {
public:
  MainWindow(State &s);
  virtual ~MainWindow() = default;

private:
};
