/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options type.h
*/

#pragma once

#include "type.h"

/**
 * @brief Parse the options of the server
 * @param argc Number of arguments
 * @param argv Arguments
 * @return options_t* The options of the server (NULL if an error occured)
 */
options_t *parse_options(int argc, char **argv);

/**
 * @brief Print the usage of the server
 */
void print_usage(void);

/**
 * @brief Free the options structure
 */
void options_destroy(options_t *options);
