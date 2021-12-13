
add_library(sqlite STATIC shell.c sqlite3.c)
target_include_directories(sqlite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
