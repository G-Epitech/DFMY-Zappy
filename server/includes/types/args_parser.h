/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "types/args_parser.h"

#define ARGS_PARSER_CURRENT(p) (p->argv[p->current])

/// @brief Structure containing the context of arguments parsing
typedef struct args_parser_s {
    // @brief The number of arguments
    int argc;
    // @brief The values of the arguments
    char **argv;
    // @brief The current argument index
    int current;
    // @brief Error status
    bool error;
} args_parser_t;

/**
 * @brief Initialize the args parser structure
 * @param parser Parser to initialize
 * @param argc Number of arguments
 * @param argv Arguments values
 */
void args_parser_init(args_parser_t *parser, int argc, char **argv);

/**
 * @brief Check if next argument is present
 * @param parser Parser to use to perform the check
 * @param error_msg Error message to display if the argument is missing
 * @param ... Arguments to pass to the error message
 * @return Next argument presence
 */
bool args_parser_has_next_arg(args_parser_t *parser,
    const char *error_msg, ...) __attribute__((format(printf, 2, 3)));
