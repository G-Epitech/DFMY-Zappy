/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** port.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types/args.h"

static bool read_port_value(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);
    char *end = NULL;

    if (args->port != -1) {
        parser->error = true;
        return fprintf(stderr, "Server port already set\n") || true;
    }
    args->port = strtol(arg, &end, 10);
    if (end == arg) {
        fprintf(stderr, "Invalid server port\n");
        parser->error = true;
    } else if (args->port < 0 || args->port > 65535) {
        fprintf(stderr, "Server port must be between in range [0, 65535]\n");
        parser->error = true;
    }
    return true;
}

bool args_parse_port(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);

    if (strcmp(arg, "--port") != 0 && strcmp(arg, "-p") != 0)
        return false;
    if (!args_parser_has_next_arg(parser,
        "Missing value for server port"
    )) {
        return true;
    }
    return read_port_value(parser, args);
}
