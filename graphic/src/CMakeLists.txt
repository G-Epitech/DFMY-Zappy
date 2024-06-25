## Source code library
add_library(zappy_gui_src STATIC)
target_link_libraries(zappy_gui_src OgreBites)

target_include_directories(zappy_gui_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(zappy_gui_src PUBLIC ${CMAKE_SOURCE_DIR})

## Binary executable
add_executable(zappy_gui main.cpp)

include_directories(${OGRE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OGRE_LIBRARIES})
target_link_libraries(zappy_gui zappy_gui_src)

## Add subdirectories
add_subdirectory(app)
add_subdirectory(commands)
add_subdirectory(types)
add_subdirectory(utils)
add_subdirectory(client)
add_subdirectory(constants)
