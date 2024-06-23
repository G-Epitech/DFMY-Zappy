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
#include "app.h"

static void read_frequency_value(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);
    char *end = NULL;

    args->frequency = strtoul(arg, &end, 10);
    if (end == arg) {
        fprintf(stderr, "Invalid frequency\n");
        parser->error = true;
    } else if (args->frequency < APP_MIN_FREQ ||
        args->frequency > APP_MAX_FREQ
    ) {
        fprintf(stderr, "Frequency value must be in range [%d, %d]\n",
            APP_MIN_FREQ, APP_MAX_FREQ
        );
        parser->error = true;
    }
}

bool args_parse_frequency_option(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);

    if (strcmp(arg, "--frequency") != 0 && strcmp(arg, "-f") != 0)
        return false;
    if (!args_parser_has_next_arg(parser, "Missing value for frequency"))
        return true;
    read_frequency_value(parser, args);
    return true;
}
