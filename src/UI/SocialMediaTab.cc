
#include "UI/SocialMediaTab.hh"

#include <FL/Fl_Table.H>


class SocialsTable : public Fl_Table {
public:
  SocialsTable(int x, int y, int w, int h, const char *l = 0)
      : Fl_Table(x, y, w, h, l) {
    col_resize(1);
    col_header_height(25);
    row_resize(0);
    row_header_width(80);
    cols(2);
    end();
  }

  void set(std::vector<SocialMedia> socials) {
    clear();
    rows(socials.size());
    cols(2);

    begin();
    for (unsigned i = 0; i < socials.size(); ++i) {
      int x, y, w, h;

      find_cell(CONTEXT_TABLE, i, 0, x, y, w, h);
      auto name = new Fl_Output(x, y, w, h);
      name->value(socials[i].getName().c_str());
      find_cell(CONTEXT_TABLE, i, 1, x, y, w, h);
      auto adres = new Fl_Output(x, y, w, h);
      adres->value(socials[i].getAddress().c_str());

      find_cell(CONTEXT_TABLE, i, 2, x, y, w, h);
    }
    end();
    redraw();
  }
};


void SocialMediaTab::initTab(){
  listOfSocials.clear();
  listOfSocials = state.getAllMedias();
  newsTable->set(listOfSocials);
}

SocialMediaTab::SocialMediaTab(State &s) : Tab("Social media", s) {
  { 
     newsTable = new SocialsTable(10, 50, 605, 390, "Social media");
  }

  initTab();
  end();
}
