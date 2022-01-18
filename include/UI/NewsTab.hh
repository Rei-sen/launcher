
#pragma once

#include "UI/Tab.hh"

#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Tree.H>
#include <GameInfo.hh>
#include <News.hh>

class NewsTab : public Tab {
public:
  NewsTab(const NewsTab &) = delete;
  NewsTab &operator=(const NewsTab &) = delete;
  virtual ~NewsTab() = default;

  static void onNewsTreeSelected(Fl_Widget *, void *);

  NewsTab(State &s);

private:
  std::vector<News> newsVector;

  //  std::vector<GameInfo> gamesWithNewsVector;
  //
  void initTabData();

  void updateTabData();

  Fl_Tree *newsTree;
  Fl_Text_Display *titleField;
  Fl_Text_Display *contentField;
  Fl_Text_Buffer *newsTitleBuf;
  Fl_Text_Buffer *newsContentBuf;
};
