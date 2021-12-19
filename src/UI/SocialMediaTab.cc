
#include "UI/SocialMediaTab.hh"

#include <FL/Fl_Table.H>

SocialMediaTab::SocialMediaTab(State &s) : Tab("Social media", s) {
  {
    Fl_Table *o = new Fl_Table(10, 35, 605, 410);
    o->cols(2);
    o->end();
  }

  end();
}
