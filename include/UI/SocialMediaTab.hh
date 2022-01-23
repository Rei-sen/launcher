
#pragma once

#include "UI/Tab.hh"
#include "SocialMedia.hh"

#include <FL/Fl_Output.H>
#include <FL/Fl_Table.H>

class SocialsTable;

class SocialMediaTab : public Tab {
public:
  SocialMediaTab(const SocialMediaTab &) = delete;
  SocialMediaTab &operator=(const SocialMediaTab &) = delete;
  virtual ~SocialMediaTab() = default;

  SocialMediaTab(State &s);
  void initTab(); 


private:
	  
	  SocialsTable *newsTable;
  std::vector<SocialMedia> listOfSocials;


};
