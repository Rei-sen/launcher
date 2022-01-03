
#include "UI/StoreTab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>



void StoreTab::searchButtonMet() {
    // dodać wyszukanie gier w bazie danych
  printf("wyszukiwanie");
  gameName->value(searchInput->value());
    
}

void StoreTab::buyButtonMet() {
    // dodać zakup gry/dlc
  printf("zakup");
}


void StoreTab::updateDlcAndNameMet() {
    // dodać załadowanie opisu do pola description oraz załadowanie listy dlc dla wybranej gry, dodatkowo ustawić nazwę gry na wybrane pole z listy produktów
  printf("aktualizacja dlc");
//    buyButton->activate();
  buyButton->activate();

}

void StoreTab::updateNameFiedlMet() {
  // dodać załadowanie opisu do pola description oraz załadowanie listy dlc dla
  // wybranej gry, dodatkowo ustawić nazwę gry na wybrane pole z listy
  // produktów
  printf("nazwa gry = nazwa dlc");
  buyButton->activate();
}


StoreTab::StoreTab(State &s) : Tab("Store", s) {
        // dodać załadowanie listy gier oraz zaznaczenie którą grę się posiada a którą nie, 
        gameList = new Fl_Browser(10, 75, 221, 370); 
        gameList->callback(updateDlcAndNameCallback, this);
   // Fl_Browser* o

  
    searchInput = new Fl_Input(10, 35, 139, 30);
    searchInput->align(Fl_Align(FL_ALIGN_CENTER));
                                               // Fl_Input* o
  
    searchButton =
        new Fl_Button(159, 35, 72, 30, "search"); // Fl_Button* o
    searchButton->callback(searchButtonCallback, this);
  
  
    Fl_Group *o = new Fl_Group(241, 35, 374, 410);
    o->box(FL_DOWN_BOX);
     gameName = new Fl_Output(302, 45, 303, 30, "Name");  // Fl_Output* o
    
      buyButton = new Fl_Button(533, 85, 72, 30, "Buy");
      // dodać callbacl
      buyButton->callback(buyButtonCallback, this);
      buyButton->deactivate();
     // Fl_Button* o
    
      priceLabel = new Fl_Output(436, 85, 56, 30, "PLN");
      priceLabel->align(Fl_Align(FL_ALIGN_RIGHT));
     // Fl_Output* priceLabel
    
      statusLabel = new Fl_Output(303, 85, 123, 30, "Staus");
     // Fl_Output* statusLabel
    
      dlcList = new Fl_Browser(251, 335, 354, 100, "DLC");
      dlcList->align(Fl_Align(FL_ALIGN_TOP));
      dlcList->callback(updateNameFiedlCallback, this);
     // Fl_Browser* o
    
      description = new Fl_Text_Display(251, 125, 354, 178);
     // Fl_Text_Display* description
    o->end();


   // Fl_Group* o
  end();
}
