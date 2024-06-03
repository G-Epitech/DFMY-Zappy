add_executable(zappy_server main.c)

target_include_directories(zappy_server PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(raytracer_server gcov)
endif()
