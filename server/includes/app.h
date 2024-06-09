/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.h
*/

#pragma once

#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 84

/**
 * @brief Main function of server
 * @param argc Number of arguments
 * @param argv Values of arguments
 * @return Exit code
 */
int app_run(int argc, char **argv);

/**
 * @brief Print the usage of the server
 */
void app_print_usage(void);
