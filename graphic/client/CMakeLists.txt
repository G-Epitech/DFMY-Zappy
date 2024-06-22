add_library(zappy_gui_client STATIC)

target_include_directories(zappy_gui_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

target_sources(zappy_gui_client PRIVATE
        Client.cpp
        Client.hpp
)
