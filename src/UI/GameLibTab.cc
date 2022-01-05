
#include "UI/GameLibTab.hh"

#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_message.H>


void GameLibTab::onPlayButton(Fl_Widget *, void *v) {
  fl_message("Game launched");
}

void GameLibTab::onInstallButton(Fl_Widget *, void *v) {
  fl_message("Game installed");
  // dodać gdzieś info o tym, że użytkownik ma zainstalowaną grę
}
void GameLibTab::onUninstallButton(Fl_Widget *, void *v) {
  fl_message("Game uninstalled");
  // dodać gdzieś info o tym, że użytkownik odinstalował grę
}
void GameLibTab::onSearchButton(Fl_Widget *, void *v) {
  // dodać wyszukanie gier i dlc w bazie danych
    // to poniżej jest po to, żeby sprawdzić czy działa callback
  printf("search");
  ((GameLibTab *)v)->gameName->value(((GameLibTab *)v)->searchInput->value());
  ((GameLibTab *)v)->playButton->activate();
  ((GameLibTab *)v)->installButton->activate();
  ((GameLibTab *)v)->installButton->activate();
}

void GameLibTab::onBrowserClick(Fl_Widget *, void *v) { 
    // to poniżej jest po to, żeby sprawdzić czy działa callback
    printf("lista");
    // dodać pobranie listy dlc dla wybranego elementu oraz przepisanie nazwy do gameName
}


GameLibTab::GameLibTab(State &s) : Tab("Game library", s) {

    gameList = new Fl_Browser(10, 75, 221, 370); 
    gameList->callback(onBrowserClick, this);

    searchInput = new Fl_Input(10, 35, 139, 30);
    searchInput->align(Fl_Align(FL_ALIGN_CENTER));
                                              
    searchButton = new Fl_Button(159, 35, 72, 30, "search"); 
    searchButton->callback(onSearchButton, this);


    Fl_Group *o = new Fl_Group(241, 35, 374, 410);
    o->box(FL_DOWN_BOX);
    gameName = new Fl_Output(302, 45, 303, 30, "Name"); 
    
    playButton = new Fl_Button(533, 85, 72, 30, "Play");
    playButton->deactivate();
    playButton->callback(onPlayButton, this);

    installButton = new Fl_Button(451, 85, 72, 30, "Install");
    installButton->callback(onInstallButton, this);

    installButton->deactivate();
      

    uninstallButton = new Fl_Button(369, 85, 72, 30, "Uninstall");
    uninstallButton->callback(onUninstallButton, this);
    uninstallButton->deactivate();
     
    
    dlcTable = new Fl_Table(251, 150, 354, 285, "DLC");
    o->end();
  end();
}
