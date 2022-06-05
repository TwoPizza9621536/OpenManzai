project(examples)
add_executable(testlib1 src/testlib1.cpp)
target_link_libraries(testlib1 OpenManzi)

install(TARGETS testlib1 RUNTIME DESTINATION ${BIN_DIR})
