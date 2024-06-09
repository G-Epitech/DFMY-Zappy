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

static bool read_size_value(args_parser_t *parser, size_t *value,
    const char *flag)
{
    char *arg = ARGS_PARSER_CURRENT(parser);
    char *end = NULL;

    if (*value > 0) {
        parser->error = true;
        return fprintf(stderr, "Map %s already set\n", flag) || true;
    }
    *value = strtoul(arg, &end, 10);
    if (end == arg) {
        fprintf(stderr, "Invalid map %s value\n", flag);
        parser->error = true;
    } else if (*value < 10 || *value > 40) {
        fprintf(stderr, "Value of map %s must be in range [10, 40]\n", flag);
        parser->error = true;
    }
    return true;
}

bool args_parse_map_size(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);
    bool height = strcmp(arg, "--height") == 0 || strcmp(arg, "-y") == 0;
    bool width = strcmp(arg, "--width") == 0 || strcmp(arg, "-x") == 0;

    if (!height && !width)
        return false;
    if (!args_parser_has_next_arg(parser,
        "Missing value for map %s", height ? "height" : "width"
    )) {
        return true;
    }
    return read_size_value(
        parser,
        height ? &args->height : &args->width,
        height ? "height" : "width"
    );
}
