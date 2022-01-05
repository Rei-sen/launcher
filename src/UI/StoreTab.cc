
#include "UI/StoreTab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>

void StoreTab::onSearchButton(Fl_Widget *, void *v) {
  // poniżej sprawdzenie czy działa - wyświetlenie komunikatu + przepisanie
  // wartości z search do name
  printf("wyszukiwanie");
  ((StoreTab *)v)->gameName->value(((StoreTab *)v)->searchInput->value());
}

void StoreTab::onBuyButton(Fl_Widget *, void *v) {
  // poniżej sprawdzenie czy działa
  fl_message("Game bought");
}

void StoreTab::onBrowserClick(Fl_Widget *, void *v) {
  // poniżej sprawdzenie czy działa
  printf("aktualizacja dlc");
  // dodać sprawdzenie czy użytkownik posiada produkcje jeżeli nie deaktywować
  // przycisk
  ((StoreTab *)v)->buyButton->activate();

  // potem poprawne przypisania dać z connecta
  ((StoreTab *)v)->priceLabel->value(((StoreTab *)v)->searchInput->value());
  ((StoreTab *)v)->statusLabel->value(((StoreTab *)v)->searchInput->value());
}

void StoreTab::onDlcBrowserClick(Fl_Widget *, void *v) {
  // dodać załadowanie opisu do pola description oraz załadowanie listy dlc dla
  // wybranej gry, dodatkowo ustawić nazwę gry na wybrane pole z listy
  // produktów
  printf("nazwa gry = nazwa dlc");
  ((StoreTab *)v)->buyButton->activate();
}

StoreTab::StoreTab(State &s) : Tab("Store", s) {
  // dodać załadowanie listy gier oraz zaznaczenie którą grę się posiada a
  // którą nie,
  gameList = new Fl_Browser(10, 75, 221, 370);
  gameList->callback(onBrowserClick, this);
  // Fl_Browser* o

  searchInput = new Fl_Input(10, 35, 139, 30);
  searchInput->align(Fl_Align(FL_ALIGN_CENTER));
  // Fl_Input* o

  searchButton = new Fl_Button(159, 35, 72, 30, "search"); // Fl_Button* o
  searchButton->callback(onSearchButton, this);

  Fl_Group *o = new Fl_Group(241, 35, 374, 410);
  o->box(FL_DOWN_BOX);
  gameName = new Fl_Output(302, 45, 303, 30, "Name"); // Fl_Output* o

  buyButton = new Fl_Button(533, 85, 72, 30, "Buy");
  // dodać callbacl
  buyButton->callback(onBuyButton, this);
  buyButton->deactivate();
  // Fl_Button* o

  priceLabel = new Fl_Output(436, 85, 56, 30, "PLN");
  priceLabel->align(Fl_Align(FL_ALIGN_RIGHT));
  // Fl_Output* priceLabel

  statusLabel = new Fl_Output(303, 85, 123, 30, "Staus");
  // Fl_Output* statusLabel

  dlcList = new Fl_Browser(251, 335, 354, 100, "DLC");
  dlcList->align(Fl_Align(FL_ALIGN_TOP));
  dlcList->callback(onDlcBrowserClick, this);
  // Fl_Browser* o

  description = new Fl_Text_Display(251, 125, 354, 178);
  // Fl_Text_Display* description
  o->end();

  // Fl_Group* o
  end();
}
