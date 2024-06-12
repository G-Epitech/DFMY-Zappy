# Project Setup
cmake_minimum_required(VERSION 3.28)
project(zappy_gui)

# Set Flags
set(CMAKE_CXX_STANDARD 20)

# Set Output Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Set package
find_package(OGRE REQUIRED)

# Add Subdirectories
add_subdirectory(src)
