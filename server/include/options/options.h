/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>

// @brief Structure containing the options of the server
typedef struct s_options {
    // @brief The port of the server
    int port;
    // @brief The width of the map
    size_t width;
    // @brief The height of the map
    size_t height;
    // @brief The number of clients allowed to connect
    size_t clients_nb;
    // @brief The frequency of the server
    size_t freq;
    // @brief The names of the teams
    char **teams;
} options_t;


/**
 * @brief Free the options structure
 */
void options_destroy(options_t *options);

/**
 * @brief Initialize the values of options structure
 * @return The options structure
 */
void options_init(options_t *options);

/**
 * @brief Parse the options of the server
 * @param argc Number of arguments
 * @param argv Arguments
 * @return The options of the server (NULL if an error occurred)
 */
bool options_parse(int argc, char **argv, options_t *options);

/**
 * @brief Print the usage of the server
 */
void print_usage(void);
