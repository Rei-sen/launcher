
#include "UI/Tab.hh"

Tab::Tab(const char *name, State &s)
    : Fl_Group(0, 25, 625, 430, name), state(s) {
  // box(FL_NO_BOX);
  // color(FL_BACKGROUND_COLOR);
  // selection_color(FL_BACKGROUND_COLOR);
  // labeltype(FL_NORMAL_LABEL);
  // labelfont(0);
  // labelsize(14);
  // labelcolor(FL_FOREGROUND_COLOR);
  // align(Fl_Align(FL_ALIGN_TOP));
  // when(FL_WHEN_RELEASE);
  hide();
}
