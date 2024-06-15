target_sources(zappy_server_tests PUBLIC
        list_tests.c
        node_tests.c
        controller_tests.c
        request_tests.c
        emission_tests.c
        server_tests.c
        smart_ptr_tests.c
)
add_subdirectory(args)
add_subdirectory(world)
