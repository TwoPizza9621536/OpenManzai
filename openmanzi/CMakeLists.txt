add_library(
    OpenManzi
    src/openmanzi.c
    src/resource_path.c
    src/sprite.c
)

target_include_directories(OpenManzi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(OpenManzi INTERFACE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
set_target_properties(OpenManzi PROPERTIES PUBLIC_HEADER include/openmanzi.h)
set_target_properties(OpenManzi PROPERTIES PUBLIC_HEADER include/sprite.h)

install(TARGETS OpenManzi RUNTIME DESTINATION ${BIN_DIR})
