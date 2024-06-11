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

#define ARGS_DEFAULT_FREQ 100

// @brief Structure containing the arguments of the server
typedef struct args_s {
    // @brief The port of the server
    long port;
    // @brief The width of the map
    size_t width;
    // @brief The height of the map
    size_t height;
    // @brief The number of clients allowed to connect
    size_t clients_nb;
    // @brief The frequency of the server
    size_t frequency;
    // @brief The names of the teams
    char **teams;
    // @brief Help requested
    bool help;
    // @brief Verbose mode
    bool verbose;
} args_t;

// @brief Function pointer to parse the options
typedef bool (*args_handler_t)(args_parser_t *, args_t *args);

/**
 * @brief Initialize the arguments structure
 * @param args Structure to initialize
 */
void args_init(args_t *args);

/**
 * @brief Free the arguments structure
 * @param args Structure to free
 */
void args_free(args_t *args);

/**
 * @brief Parse flag from the command line
 * @param parser Current parser structure
 * @param args Arguments to fill
 * @return true if the option was parsed, false otherwise
 */
bool args_parse_flag(args_parser_t *parser, args_t *args);

/**
 * @brief Parse the command line arguments
 * @param argc Number of arguments
 * @param argv Value of the arguments
 * @param args Parsed arguments
 * @return true if the arguments were parsed, false otherwise
 */
bool args_parse(int argc, char **argv, args_t *args);

/**
 * @brief Check if the arguments are valid
 * @param args Arguments to check
 * @return true if the arguments are valid, false otherwise
 */
bool args_are_valid(args_t *args);

/**
 * @brief Parse port option
 * @param parser Parser instance
 * @param args Arguments to fill
 * @return true if the option was parsed, false otherwise
 */
bool args_parse_port(args_parser_t *parser, args_t *args);

/**
 * @brief Parse map size component
 * @param parser Parser instance
 * @param args Arguments to fill
 * @return true if the option was parsed, false otherwise
 */
bool args_parse_map_size(args_parser_t *parser, args_t *args);

/**
 * @brief Parse clients number option
 * @param parser Parser instance
 * @param args Arguments to fill
 * @return true if the option was parsed, false otherwise
 */
bool args_parse_clients_nb(args_parser_t *parser, args_t *args);

/**
 * @brief Parse teams
 * @param parser Parser instance
 * @param args Arguments to fill
 * @return true if the option was parsed, false otherwise
 */
bool args_parse_teams(args_parser_t *parser, args_t *args);

/**
 * @brief Parse frequency option
 * @param parser Parser instance
 * @param args Arguments to fill
 * @return true if the option was parsed, false otherwise
 */
bool args_parse_frequency_option(args_parser_t *parser, args_t *args);

/**
 * @brief Parse help option
 * @param parser Parser instance
 * @param args Arguments to fill
 * @return true if the option was parsed, false otherwise
 */
bool args_parse_help_option(args_parser_t *parser, args_t *args);
