target_sources(zappy_server_core PUBLIC
        new.c
        free.c
)

add_subdirectory(eggs)
add_subdirectory(players)
add_subdirectory(teams)
add_subdirectory(chrono)
add_subdirectory(resource)
