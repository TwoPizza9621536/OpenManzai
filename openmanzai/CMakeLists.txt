# SPDX-FileCopyrightText: 2022 OpenManzai Contributors
#
# SPDX-License-Identifier: CC0-1.0

add_library(OpenManzai src/OpenManzai.c src/OpenManzai_background.c src/OpenManzai_character.c src/OpenManzai_sprite.c)

target_include_directories(OpenManzai PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS}
                                             ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(OpenManzai INTERFACE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
set_target_properties(
    OpenManzai
    PROPERTIES PUBLIC_HEADER include/OpenManzai.h
               PUBLIC_HEADER include/OpenManzai_background.h
               PUBLIC_HEADER include/OpenManzai_character.h
               PUBLIC_HEADER include/OpenManzai_sprite.h)
set_target_properties(OpenManzai PROPERTIES POSITION_INDEPENDENT_CODE On)
