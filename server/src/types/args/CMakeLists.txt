target_sources(zappy_server_core PUBLIC
        free.c
        init.c
        parse.c
        parse_flag.c
        valid.c
        flags/port.c
        flags/map_size.c
        flags/teams.c
        flags/clients_nb.c
        flags/options/help.c
        flags/options/frequency.c
        flags/options/verbose_level.c
)
