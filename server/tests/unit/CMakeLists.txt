include_directories(../../include)

enable_testing()

add_executable(zappy_server_tests)

add_subdirectory(types)

target_link_libraries(zappy_server_tests
        criterion
        zappy_server_core
)
