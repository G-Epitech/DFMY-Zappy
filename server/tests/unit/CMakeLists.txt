include_directories(${PROJECT_SOURCE_DIR}/include)

enable_testing()

add_executable(zappy_server_tests test.c)

target_link_libraries(zappy_server_tests
        criterion
        zappy_server_core
)
