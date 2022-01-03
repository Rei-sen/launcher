
#include "UI/GameLibTab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Table.H>


void GameLibTab::updateDlcAndNameMet() {
  // dodać załadowanie opisu do pola description oraz załadowanie listy dlc dla
  // wybranej gry, dodatkowo ustawić nazwę gry na wybrane pole z listy
  // produktów
  printf("wybor");

  // potem dać sprawdzenie stanu gry - czy jest zainstalowana i odpowiednio aktywować przyciski

  playButton->activate();
  uninnstallButton->activate();
  innstallButton->activate();
  gameName->value(searchInput->value());
}


void GameLibTab::searchButtonMet() {
  // dodać wyszukanie gier i dlc w bazie danych 
  printf("search");
  gameName->value(searchInput->value());
}

void GameLibTab::playButtonMet() {
// dodać komunikat imitujący poprawne uruchomienie gry
  printf("play");

}


void GameLibTab::instalButtonMet() {
  // dodać komunikat o instalowaniu gry, uaktywnić przycisk do gry i odinstalowania
  printf("instal");
}


void GameLibTab::uninstallButtonMet() {
  // dodać komunikat o odinstalowaniu gry, deaktywować przycisk do gry
  printf("uninstall");
//  buyButton->activate();
}


GameLibTab::GameLibTab(State &s) : Tab("Game library", s) {

    gameList = new Fl_Browser(10, 75, 221, 370); 
    gameList->callback(updateDlcAndNameCallback, this);

    searchInput = new Fl_Input(10, 35, 139, 30);
    searchInput->align(Fl_Align(FL_ALIGN_CENTER));
                                              
    searchButton = new Fl_Button(159, 35, 72, 30, "search"); 
    searchButton->callback(searchButtonCallback, this);


    Fl_Group *o = new Fl_Group(241, 35, 374, 410);
    o->box(FL_DOWN_BOX);
    gameName = new Fl_Output(302, 45, 303, 30, "Name"); 
    
    playButton = new Fl_Button(533, 85, 72, 30, "Play");
    playButton->deactivate();
    playButton->callback(playButtonCallback, this);

    innstallButton = new Fl_Button(451, 85, 72, 30, "Install");
    innstallButton->callback(instalButtonCallback, this);

    innstallButton->deactivate();
      

    uninnstallButton = new Fl_Button(369, 85, 72, 30, "Uninstall");
    uninnstallButton->callback(uninstalButtonCallback, this);
    uninnstallButton->deactivate();
     
    
    dlcTab = new Fl_Table(251, 150, 354, 285, "DLC");
    o->end();
  end();
}
