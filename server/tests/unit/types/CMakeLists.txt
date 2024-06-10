target_sources(zappy_server_tests PUBLIC
        list_tests.c
        node_tests.c
        controller_tests.c
        request_tests.c
        emission_tests.c
        shared_event_tests.c
)
add_subdirectory(args)
