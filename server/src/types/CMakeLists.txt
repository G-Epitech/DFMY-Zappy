target_sources(zappy_server_core PUBLIC
        args_parser/init.c
        args_parser/is_valid_next_arg.c
        args/init.c
        args/free.c
        args/parse.c
        args/parse_flag.c
        args/valid.c
        args/flags/port.c
        args/flags/map_size.c
        args/flags/options/frequency.c
        args/flags/options/help.c
        args/flags/clients_nb.c
        args/flags/teams.c
)
