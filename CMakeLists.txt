cmake_minimum_required(VERSION 3.10)
project("Open Manzi" VERSION 0.0.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)

option(BUILD_SHARED_LIBS "Build shared libraries" True)

add_subdirectory(openmanzi)
add_subdirectory(examples)
