
#include "UI/GameLibTab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Table.H>

GameLibTab::GameLibTab(State &s) : Tab("Game library", s) {

  { new Fl_Browser(10, 75, 221, 370); } // Fl_Browser* o
  {
    Fl_Input *o = new Fl_Input(10, 35, 139, 30);
    o->align(Fl_Align(FL_ALIGN_CENTER));
  }                                             // Fl_Input* o
  { new Fl_Button(159, 35, 72, 30, "search"); } // Fl_Button* o
  {
    Fl_Group *o = new Fl_Group(241, 35, 374, 410);
    o->box(FL_DOWN_BOX);
    { new Fl_Output(302, 45, 303, 30, "Name"); } // Fl_Output* o
    {
      Fl_Button *o = new Fl_Button(533, 85, 72, 30, "Play");
      o->deactivate();
    } // Fl_Button* o
    {
      Fl_Table *o = new Fl_Table(251, 150, 354, 285, "DLC");
      o->end();
    } // Fl_Table* o
    {
      Fl_Button *o = new Fl_Button(451, 85, 72, 30, "Install");
      o->deactivate();
    } // Fl_Button* o
    {
      Fl_Button *o = new Fl_Button(369, 85, 72, 30, "Uninstall");
      o->deactivate();
    } // Fl_Button* o
    o->end();
  } // Fl_Group* o

  end();
}
