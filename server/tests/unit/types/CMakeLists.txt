target_sources(zappy_server_tests PUBLIC
        list_tests.c
        node_tests.c
)
add_subdirectory(args)
add_subdirectory(world)
