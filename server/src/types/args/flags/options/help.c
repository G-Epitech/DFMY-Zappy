/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** port.c
*/

#include <string.h>
#include "types/args.h"

bool args_parse_help_option(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);

    if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0) {
        args->help = true;
        return true;
    }
    return false;
}
