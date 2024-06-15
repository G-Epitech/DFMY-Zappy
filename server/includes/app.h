/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.h
*/

#pragma once

#include <stdbool.h>
#include "log.h"
#include "types/server.h"
#include "types/args.h"

#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 84
#define APP_RUNNING (*app_stopped() == false)

// @brief Application state
typedef struct app_s {
    // @brief Server instance
    server_t *server;
    // @brief Program arguments
    args_t args;
} app_t;

/**
 * @brief Provide access to the application state
 * @return Current value of the application state
 */
bool *app_stopped(void);

/**
 * @brief Initialize the application
 * @param app Application to initialize
 */
void app_init(app_t *app);

/**
 * @brief Stop the application
 */
void app_stop(void);

/**
 * @brief Exit the application
 * @param app Application to exit
 * @param code Exit code
 * @return Exit code
 */
int app_exit(app_t *app, int code);

/**
 * @brief Start the application
 * @param argc Number of arguments
 * @param argv Values of arguments
 * @return Exit code
 */
int app_start(int argc, char **argv);

/**
 * @brief Running loop of the application
 * @param app Application to run
 * @return Exit code
 */
int app_run(app_t *app);

/**
 * @brief Print the usage of the server
 */
void app_print_usage(void);

/**
 * @brief Setup signal handlers
 */
void app_setup_sig_handlers(void);
