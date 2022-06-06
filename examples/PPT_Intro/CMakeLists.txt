# SPDX-FileCopyrightText: 2022 OpenManzi Contributors
#
# SPDX-License-Identifier: CC0-1.0

project(examples)
add_executable(PPT_Intro src/PPT_Intro.cpp)
target_link_libraries(PPT_Intro OpenManzi)

install(TARGETS PPT_Intro RUNTIME DESTINATION ${BIN_DIR})
