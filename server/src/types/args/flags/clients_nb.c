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

static bool read_clients_nb_value(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);
    char *end = NULL;

    if (args->clients_nb > 0) {
        parser->error = true;
        return fprintf(stderr, "Number of clients already set\n") || true;
    }
    args->clients_nb = strtoul(arg, &end, 10);
    if (end == arg) {
        fprintf(stderr, "Invalid number of clients\n");
        parser->error = true;
    } else if (args->clients_nb < 1 || args->clients_nb > 200) {
        fprintf(stderr, "Number of clients must be in range [1, 200]\n");
        parser->error = true;
    }
    return true;
}

bool args_parse_clients_nb(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);

    if (strcmp(arg, "--clients-nb") != 0 && strcmp(arg, "-c") != 0)
        return false;
    if (!args_parser_has_next_arg(
        parser,
        "Missing value for number of clients"
    )) {
        return true;
    }
    return read_clients_nb_value(parser, args);
}
