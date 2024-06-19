target_sources(zappy_server_core PUBLIC
        start.c
        run.c
        usage.c
        stop.c
        init.c
        pipeline.c
)
add_subdirectory(steps)
add_subdirectory(world)
