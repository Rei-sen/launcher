
add_library(sqlite STATIC sqlite3.c)
add_executable(sqliteshell shell.c sqlite3.c)
if (MSVC)
else()
  target_link_libraries(sqliteshell dl pthread)
endif()
target_include_directories(sqlite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
