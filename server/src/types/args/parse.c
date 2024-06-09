/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options parser
*/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "types/args.h"

static bool parsing_error(args_parser_t *parser)
{
    char *arg = ARGS_PARSER_CURRENT(parser);

    if (arg[0] == '-') {
        fprintf(stderr, "Invalid flag: %s\n", arg);
    } else {
        fprintf(stderr, "Invalid argument: %s\n", arg);
    }
    return false;
}

static bool parse_arg(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);

    return arg[0] == '-' ? args_parse_flag(parser, args) : false;
}

bool args_parse(int argc, char **argv, args_t *args)
{
    args_parser_t parser;

    args_parser_init(&parser, argc, argv);
    while (parser.current < parser.argc && !parser.error) {
        if (!parse_arg(&parser, args))
            return parsing_error(&parser);
        parser.current += 1;
    }
    return parser.error ? false : true;
}
