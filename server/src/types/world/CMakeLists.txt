target_sources(zappy_server_core PUBLIC
        new.c
        free.c
        delay.c
)

add_subdirectory(egg)
add_subdirectory(player)
add_subdirectory(team)
add_subdirectory(chrono)
add_subdirectory(incantation)
add_subdirectory(resources_manager)
add_subdirectory(map)
