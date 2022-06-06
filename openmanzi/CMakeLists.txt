# SPDX-FileCopyrightText: 2022 OpenManzi Contributors
#
# SPDX-License-Identifier: CC0-1.0

add_library(OpenManzi src/OpenManzi.c src/OpenManzi_sprite.c)

target_include_directories(
    OpenManzi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS}
                     ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(OpenManzi INTERFACE ${SDL2_LIBRARIES}
                                          ${SDL2_IMAGE_LIBRARIES})
set_target_properties(
    OpenManzi PROPERTIES PUBLIC_HEADER include/OpenManzi.h
                         PUBLIC_HEADER include/OpenManzi_sprite.h)
set_target_properties(OpenManzi PROPERTIES POSITION_INDEPENDENT_CODE On)
