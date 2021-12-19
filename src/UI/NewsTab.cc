
#include "UI/NewsTab.hh"

#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Tree.H>

NewsTab::NewsTab(State &s) : Tab("News", s) {
  { new Fl_Tree(10, 35, 221, 410); }          // Fl_Tree* o
  { new Fl_Text_Display(241, 35, 374, 30); }  // Fl_Text_Display* o
  { new Fl_Text_Display(241, 75, 374, 370); } // Fl_Text_Display* o

  end();
}
