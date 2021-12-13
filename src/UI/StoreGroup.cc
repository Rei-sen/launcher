
#include "UI/StoreGroup.hh"

StoreGroup::StoreGroup(int X, int Y, int W, int H, const char *L)
    : Fl_Group(X, Y, W, H, L) {
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
      Fl_Button *o = new Fl_Button(533, 85, 72, 30, "Buy");
      o->deactivate();
    } // Fl_Button* o
    {
      priceLabel = new Fl_Output(436, 85, 56, 30, "PLN");
      priceLabel->align(Fl_Align(FL_ALIGN_RIGHT));
    } // Fl_Output* priceLabel
    {
      statusLabel = new Fl_Output(303, 85, 123, 30, "Staus");
    } // Fl_Output* statusLabel
    {
      Fl_Browser *o = new Fl_Browser(251, 335, 354, 100, "DLC");
      o->align(Fl_Align(FL_ALIGN_TOP));
    } // Fl_Browser* o
    {
      description = new Fl_Text_Display(251, 125, 354, 178);
    } // Fl_Text_Display* description
    o->end();
  } // Fl_Group* o
  end();
}
