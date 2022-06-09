# SPDX-FileCopyrightText: 2022 OpenManzai Contributors
#
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required(VERSION 3.12)
project(
    OpenManzai
    VERSION 0.0.0
    LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(
        FATAL_ERROR
            "Please run cmake in a build directory instead of running cmake inside of OpenManzai source directory.")
endif()

set(BIN_DIR ${OpenManzai_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED On)
set(CMAKE_C_EXTENSIONS Off)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

option(BUILD_SHARED_LIBS "Build shared libraries" On)
option(BUILD_EXAMPLES "Build examples applications" Off)
option(CMAKE_VERBOSE_MAKEFILE "Have verbose output" Off)
option(CMAKE_BUILD_TYPE "Set build type" Debug)
option(CMAKE_INSTALL_PREFIX "Set installation prefix" /usr/local)

if(MSVC)
    add_compile_options(/W4 /Wall /WX /guard:cf /sdl /GS)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    add_compile_options(
        -Wall
        -Wextra
        -Werror
        -Wsign-conversion
        -pedantic
        -fstack-clash-protection
        -fstack-protector)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS}  ${CMAKE_C_FLAGS_DEBUG} -g")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} -O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}  ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)

if(NOT ${SDL2_FOUND} OR NOT ${SDL2_IMAGE_FOUND})
    find_package(SDL2 REQUIRED)
    find_package(SDL2_IMAGE REQUIRED)
endif()

add_subdirectory(openmanzai)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)

    if(NOT ${PROJECT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
        file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
    endif()
endif()
