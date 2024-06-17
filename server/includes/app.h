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

// @brief Application state
typedef struct app_s {
    // @brief Server instance
    server_t *server;
    // @brief Program arguments
    args_t args;
    // @brief Application running state
    volatile bool running;
} app_t;

/**
 * @brief Set the target of the signal handler
 * @param app Application to set the target
 * @param set Set the target
 * @return Current target of the signal handler
 */
app_t *app_sig_handlers_target(app_t *app, bool set);

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
