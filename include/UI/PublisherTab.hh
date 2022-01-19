
#pragma once

#include "FL/Fl_Hold_Browser.H"
#include <FL/Fl_Browser.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Editor.H>
#include <UI/Tab.hh>

class PublisherTab : public Tab {
public:
  PublisherTab(const PublisherTab &) = delete;
  PublisherTab &operator=(const PublisherTab &) = delete;
  virtual ~PublisherTab() = default;

  PublisherTab(State &s);

private:
  void initAllGroups();
  void initGameGroup();
  void initNewsGroup();
  void updateGameGroup();
  void updateNewsGroup();

  static void onGameBrowserSelected(Fl_Widget *, void *);
  static void onNewsTreeSelected(Fl_Widget *, void *);

  static void onUpdateGame(Fl_Widget *, void *);
  static void onUpdateNews(Fl_Widget *, void *);
  static void onAddNews(Fl_Widget *, void *);

private:
  Fl_Hold_Browser *gameBrowser;
  Fl_Input *gameName;
  Fl_Float_Input *gamePrice;
  Fl_Text_Editor *gameDescription;
  Fl_Text_Buffer *gameDescriptionBuf;
  Fl_Button *updateGameButton;
  // group of news
  Fl_Tree *newsTree;
  Fl_Input *newsTitle;
  Fl_Text_Editor *newsContent;
  Fl_Text_Buffer *newsContentBuf;
  Fl_Button *newsUpdateAdd;
  // socials
  Fl_Input *socialsAddress;
  Fl_Button *socialsUpdate;
  Fl_Choice *socialsPlatform;
  Fl_Button *socialsAddNew;
};
