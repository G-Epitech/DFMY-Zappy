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
#include "types/trantor/world.h"

#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 84

// @brief Application state
typedef struct app_s {
    // @brief Server instance
    server_t *server;
    // @brief Program arguments
    args_t args;
    // @brief World instance
    world_t *world;
    // @brief Application running state
    volatile bool running;
} app_t;

// @brief App step function prototype
typedef void (*app_step_t)(app_t *app);

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

/**
 * @brief Run the application pipeline
 * @param app Application with which run the pipeline
 */
void app_run_pipeline(app_t *app);

/**
 * @brief Handle server connections
 * @param app Application to handle the server connections
 */
void app_handle_server_connections(app_t *app);

/**
 * @brief Handle world lifecycle of players
 * @param server Server to handle the world lifecycle of players
 * @param world World to handle the world lifecycle of players
 */
void app_handle_world_lifecycle_players(server_t *server, world_t *world);

/**
 * @brief Handle world lifecycle
 * @param app Application to handle the world lifecycle
 */
void app_handle_world_lifecycle(app_t *app);

/**
 * @brief Handle server select timeout
 * @param app Application to handle the server select timeout
 * @param timeout Timeout to change
 * @return Pointer to given timeout or NULL if no timeout have to be set
 */
timeval_t *app_get_timeout(app_t *app, timeval_t *timeout);

/**
 * @brief Handle application routines step
 * @param app Application to handle the routines
 */
void app_handle_world_routines(app_t *app);

/**
 * @brief Handle world routine resources generation
 * @param world World to handle the routine resources generation
 */
void app_handle_world_routine_resources_generation(world_t *world);

/**
 * @brief Handle world routine team victory
 * @param world World to handle the routine team victory
 * @param server Server to handle the routine team victory
 * @return true if a team has won, false otherwise
 */
bool app_handle_world_routine_team_victory(world_t *world, server_t *server);
