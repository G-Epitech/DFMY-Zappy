# Global settings
cmake_minimum_required(VERSION 3.27)
project(zappy_server C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Project targets
add_library(zappy_server_core STATIC)
target_include_directories(zappy_server_core PUBLIC includes)
target_link_libraries(zappy_server_core m)
add_subdirectory(src)

add_executable(zappy_server main.c)
target_link_libraries(zappy_server zappy_server_core)
target_include_directories(zappy_server PUBLIC includes)

# Tests
if (COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    target_link_libraries(zappy_server_core gcov)
endif()

add_subdirectory(tests/unit)
