/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** parse.c
*/

#include "types/args.h"

static const args_handler_t handlers[] = {
    &args_parse_port,
    &args_parse_map_size,
    &args_parse_teams,
    &args_parse_clients_nb,
    &args_parse_help_option,
    &args_parse_frequency_option,
    NULL
};

bool args_parse_flag(args_parser_t *parser, args_t *args)
{
    size_t handler_index = 0;

    while (handlers[handler_index] != NULL) {
        if (handlers[handler_index](parser, args))
            return true;
        handler_index += 1;
    }
    return false;
}
