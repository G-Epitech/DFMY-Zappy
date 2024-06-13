/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** port.c
*/

#include <stdio.h>
#include <string.h>
#include "types/args.h"

static void read_verbose_level_value(args_parser_t *parser, args_t *args)
{
    const char *str_levels[] = { "INFO", "DEBUG", "ERROR", "WARNING" };
    const log_level_t levels[] = { LOG_INFO, LOG_DEBUG, LOG_ERROR, LOG_WARN };
    const size_t nb_levels = sizeof(levels) / sizeof(*levels);
    char *arg = ARGS_PARSER_CURRENT(parser);

    for (size_t i = 0; i < nb_levels; i++) {
        if (strcmp(arg, str_levels[i]) == 0) {
            args->verbose_level = levels[i];
            return;
        }
    }
    fprintf(stderr, "Invalid verbose level: %s\n", arg);
    parser->error = true;
}

bool args_parse_verbose_level_option(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);

    if (strcmp(arg, "--verbose-level") != 0 && strcmp(arg, "-v") != 0)
        return false;
    if (!args_parser_has_next_arg(parser, "Missing value for verbose level"))
        return true;
    read_verbose_level_value(parser, args);
    return true;
}
