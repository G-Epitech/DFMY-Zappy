/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.h
*/

#pragma once

#include <stdbool.h>
#include "log.h"

#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 84
#define APP_RUNNING (*app_stopped() == false)

/**
 * @brief Provide access to the application state
 * @return Current value of the application state
 */
bool *app_stopped(void);

/**
 * @brief Provide access to the application verbose level
 * @return Current value of the application verbose level
 */
log_level_t *app_verbose_level(void);

/**
 * @brief Stop the application
 */
void app_stop(void);

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
