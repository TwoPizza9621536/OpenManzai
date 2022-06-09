# SPDX-FileCopyrightText: 2022 OpenManzai Contributors
#
# SPDX-License-Identifier: CC0-1.0

add_executable(PPT_Intro src/PPT_Intro.c)
target_link_libraries(PPT_Intro OpenManzai)

install(TARGETS PPT_Intro RUNTIME DESTINATION ${BIN_DIR})
