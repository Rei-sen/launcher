
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

void PublisherTab::onUpdateGameButton(Fl_Widget *, void *v) {
  fl_message("Game Added/Updated");
}
void PublisherTab::onUpdateNewsButton(Fl_Widget *, void *v) {
  fl_message("News Added/Updated");
}
void PublisherTab::onAddSocialButton(Fl_Widget *, void *v) {
  fl_message("Socials Added");
}
void PublisherTab::onUpdateSocialButton(Fl_Widget *, void *v) {
  fl_message("Socials Updated");
}

PublisherTab::PublisherTab(State &s) : Tab("Publisher", s) {

  {
    Fl_Scroll *o = new Fl_Scroll(0, 25, 625, 430);
    o->type(2);
    {
      Fl_Group *o = new Fl_Group(10, 57, 590, 150, "Games");
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));

      gameBrowser = new Fl_Browser(10, 67, 156, 125);
      gameBrowser->type(1);

      gameName = new Fl_Input(210, 70, 140, 30, "Name");

      price = new Fl_Float_Input(210, 110, 140, 30, "Price");
      price->type(1);

      description = new Fl_Text_Editor(360, 70, 230, 122, "Description");

      updateGame = new Fl_Button(278, 172, 72, 20, "Update");
      updateGame->callback(onUpdateGameButton, this);
      o->end();
    } // Fl_Group* o
    {
      Fl_Group *o = new Fl_Group(5, 239, 595, 206, "News");
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { new Fl_Tree(10, 245, 155, 170); }                       // Fl_Tree* o
      { newsTitle = new Fl_Input(230, 245, 360, 30, "title"); } // Fl_Input* o
      {
        newsUpdateAdd = new Fl_Button(500, 410, 90, 25, "Update/Add");
        newsUpdateAdd->callback(onUpdateNewsButton, this);

      } // Fl_Button* o
      {
        newsContent = new Fl_Text_Editor(230, 285, 360, 115, "Content");
        o->align(Fl_Align(FL_ALIGN_LEFT));
      } // Fl_Text_Editor* o
      o->end();
    } // Fl_Group* o
    {
      Fl_Group *o = new Fl_Group(10, 472, 589, 46, "Social media");
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      {
        socialsAddress = new Fl_Input(272, 478, 153, 30, "Address");
      } // Fl_Input* o
      {
        socialsUpdate = new Fl_Button(435, 478, 69, 30, "Update");
        socialsUpdate->callback(onUpdateSocialButton, this);

      } // Fl_Button* o
      {
        socialsPlatform = new Fl_Choice(84, 478, 120, 30, "Platform");
        socialsPlatform->down_box(FL_BORDER_BOX);
      } // Fl_Choice* o
      {
        socialsAddNew =
            new Fl_Button(514, 478, 75, 30, "Add new"); // onUpdateSocialButton
        socialsAddNew->callback(onAddSocialButton, this);
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    o->end();
  } // Fl_Scroll* o
}
