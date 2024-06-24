target_sources(zappy_server_tests PUBLIC
        list_tests.c
        node_tests.c
        controller_tests.c
        request_tests.c
        vector2_tests.c
        buffer_tests.c
        direction_tests.c
)
add_subdirectory(args)
add_subdirectory(trantor)
add_subdirectory(server)
