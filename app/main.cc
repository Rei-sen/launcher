
#include <iostream>

#include <sqlite3.h>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>

#include "UI/LoginForm.hh"
#include "UI/MainWindow.hh"

int main(int argc, char **argv) {
  sqlite3 *db;
  sqlite3_stmt *res;

  int rc = sqlite3_open(":memory:", &db);

  if (rc != SQLITE_OK) {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);

    return 1;
  }

  rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);

  if (rc != SQLITE_OK) {
    std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);

    return 1;
  }

  rc = sqlite3_step(res);
  if (rc == SQLITE_ROW) {
    std::cout << sqlite3_column_text(res, 0) << std::endl;
  }
  sqlite3_finalize(res);
  sqlite3_close(db);

  /* oczywiście to co wyżej do usunięcia a to co niżej do poprawy */
  Connection c;
  LoginForm f(c);
  f.show();

  State state;

  MainWindow w(state);
  w.show();

  return Fl::run();
}
