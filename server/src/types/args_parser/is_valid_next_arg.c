/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** is_valid_next_arg.cpp
*/

#include <stdio.h>
#include <stdarg.h>
#include "types/args_parser.h"

bool args_parser_has_next_arg(args_parser_t *parser,
    const char *error_msg, ...)
{
    char *arg = NULL;
    va_list printf_args;

    va_start(printf_args, error_msg);
    parser->current += 1;
    if (parser->current < parser->argc)
        arg = ARGS_PARSER_CURRENT(parser);
    if (arg == NULL) {
        vfprintf(stderr, error_msg, printf_args);
        fprintf(stderr, "\n");
        parser->error = true;
    }
    va_end(printf_args);
    return arg != NULL;
}
