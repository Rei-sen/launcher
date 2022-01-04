
#pragma once

#include <UI/Tab.hh>
#include <FL/Fl_Output.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Browser.H>

class PublisherTab : public Tab {
public:
  PublisherTab(const PublisherTab &) = delete;
  PublisherTab &operator=(const PublisherTab &) = delete;
  virtual ~PublisherTab() = default;

  PublisherTab(State &s);
  static void onUpdateGameButton(Fl_Widget *, void *v);
  static void onUpdateNewsButton(Fl_Widget *, void *v);
  static void onAddSocialButton(Fl_Widget *, void *v);
  static void onUpdateSocialButton(Fl_Widget *, void *v);

  private:
  Fl_Browser *gamebrowser;//idk jak to ma działać 
  Fl_Input *gamename;
  Fl_Float_Input *price;
  Fl_Text_Editor *description;
  Fl_Button *updategame;
  //group of news
  Fl_Input *newstitle;
  Fl_Text_Editor *newscontent;
  Fl_Button *newsupdateadd;
  //socials
  Fl_Input *socialsaddress;
  Fl_Button *socialsUpdate;
  Fl_Choice *socialsPlatform;
  Fl_Button *socialsAddNew;



};
