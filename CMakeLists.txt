cmake_minimum_required(VERSION 3.13)

project(GameLauncher LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)

if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR
    "You cannot build in a source directory (or any directory with "
    "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
    "remove CMakeCache.txt and CMakeFiles.")
endif()

set(CMAKE_CXX_STANDARD 20)

option(FLTK_BUILD_TEST OFF)
add_subdirectory(lib)
#set(FLTK_BUILD_TEST OFF CACHE BOOL "Build fltk without test programs")


include_directories(${PROJECT_SOURCE_DIR}/lib/fltk)

file(GLOB_RECURSE SRC_FILES src/*.cc)
add_executable(Launcher ${SRC_FILES} app/main.cc)

target_include_directories(Launcher PRIVATE include)

target_link_libraries(Launcher sqlite ${FLTK_LIBRARIES} fltk)

if (MSVC)
  target_compile_options(Launcher PRIVATE /W2)
else()
  target_compile_options(Launcher PRIVATE -Wall -Wextra)
  target_link_libraries(Launcher dl pthread)
endif()

