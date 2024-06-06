include_directories(../../include)

enable_testing()

add_executable(zappy_server_tests test.c)

add_subdirectory(options)

target_link_libraries(zappy_server_tests
        criterion
        zappy_server_core
)
