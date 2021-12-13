
#include "UI/MainWindow.hh"

Fl_Double_Window *MainWindow::show() {
  Fl_Double_Window *w;
  {
    Fl_Double_Window *o = new Fl_Double_Window(625, 455, "Game launcher");
    w = o;
    if (w) { /* empty */
    }
    o->user_data((void *)(this));
    {
      Fl_Tabs *o = new Fl_Tabs(0, 0, 625, 535);
      {
        StoreGroup *o = new StoreGroup(0, 25, 625, 430, "Store");
        o->box(FL_NO_BOX);
        o->color(FL_BACKGROUND_COLOR);
        o->selection_color(FL_BACKGROUND_COLOR);
        o->labeltype(FL_NORMAL_LABEL);
        o->labelfont(0);
        o->labelsize(14);
        o->labelcolor(FL_FOREGROUND_COLOR);
        o->align(Fl_Align(FL_ALIGN_TOP));
        o->when(FL_WHEN_RELEASE);
        o->hide();
        o->end();
      } // StoreGroup* o
      {
        GameLibGroup *o = new GameLibGroup(0, 24, 625, 511, "Game library");
        o->box(FL_NO_BOX);
        o->color(FL_BACKGROUND_COLOR);
        o->selection_color(FL_BACKGROUND_COLOR);
        o->labeltype(FL_NORMAL_LABEL);
        o->labelfont(0);
        o->labelsize(14);
        o->labelcolor(FL_FOREGROUND_COLOR);
        o->align(Fl_Align(FL_ALIGN_TOP));
        o->when(FL_WHEN_RELEASE);
        o->hide();
        o->end();
      } // GameLibGroup* o
      {
        PublisherGroup *o = new PublisherGroup(0, 25, 625, 430, "Publisher");
        o->box(FL_NO_BOX);
        o->color(FL_BACKGROUND_COLOR);
        o->selection_color(FL_BACKGROUND_COLOR);
        o->labeltype(FL_NORMAL_LABEL);
        o->labelfont(0);
        o->labelsize(14);
        o->labelcolor(FL_FOREGROUND_COLOR);
        o->align(Fl_Align(FL_ALIGN_TOP));
        o->when(FL_WHEN_RELEASE);
        o->end();
      } // PublisherGroup* o
      o->end();
    } // Fl_Tabs* o
    o->end();
  } // Fl_Double_Window* o
  return w;
}
