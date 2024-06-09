/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** init.c
*/

#include "types/args_parser.h"

void args_parser_init(args_parser_t *parser, int argc, char **argv)
{
    parser->argc = argc;
    parser->argv = argv;
    parser->current = 1;
    parser->error = false;
}
