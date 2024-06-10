target_sources(zappy_server_tests PUBLIC
        list_tests.c
        node_tests.c
)
add_subdirectory(args)
add_subdirectory(chrono)
add_subdirectory(egg)
add_subdirectory(player)
add_subdirectory(resource)
add_subdirectory(team)
add_subdirectory(world)
