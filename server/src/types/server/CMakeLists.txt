target_sources(zappy_server_core PRIVATE
        new.c
        free.c
        start.c
        poll.c
        fd_states.c
        connection/accept.c
        connection/close.c
        connection/get.c
        connection/incoming.c
        connection/emissions.c
)
