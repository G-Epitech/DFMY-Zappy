/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** zappy_server.h
*/

/** @defgroup server_app Server App Module
 *  Main server application module
 *  @{
 */

#pragma once

#include <stdbool.h>
#include "log.h"
#include "types/server.h"
#include "types/args.h"
#include "types/trantor/world.h"

#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 84
#define APP_MAX_FREQ 10000
#define APP_MIN_FREQ 0

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
 * @param world World to handle the world lifecycle of players
 * @param server App server instance
 */
void app_handle_world_lifecycle_players(world_t *world, server_t *server);

/**
 * @brief Handle world lifecycle update of events delays
 * @param world World to handle the world lifecycle update of events delays
 * @param server App server instance
 */
void app_handle_world_lifecycle_events_delay(world_t *world,
    server_t *server);

/**
 * @brief Handle world lifecycle game starting
 * @param world World to handle the world lifecycle game starting
 * @param server Server to handle the world lifecycle game starting
 */
void app_handle_world_lifecycle_game_starting(world_t *world,
    server_t *server);

/**
 * @brief Handle world lifecycle incantations
 * @param world World to handle the world lifecycle incantations
 * @param server App server instance
 */
void app_handle_world_lifecycle_incantations(world_t *world,
    server_t *server);

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

/**
 * @brief Handle world routine map updates
 * @param world World to handle the routine map updates
 * @param server Server to handle the routine map updates
 */
void app_handle_world_routine_map_updates(world_t *world, server_t *server);

/**
 * @brief Handle controllers requests
 * @param app App instance
 */
void app_handle_controllers_requests(app_t *app);

/**
 * @brief Promote an unknown controller to graphic controller
 * @param app App instance
 * @param controller Controller to promote
 */
void app_try_promote_controller_to_graphic(app_t *app,
    controller_t *controller);

/**
 * @brief Promote an unknown controller to player controller
 * @param app App instance
 * @param controller Controller to promote
 * @param request Request to promote
 * @param team_name_len Length of the team name
 */
void app_try_promote_controller_to_player(app_t *app,
    controller_t *controller, request_t *request, size_t team_name_len);

/**
 * @brief Handle request of an unknown controller
 * @param app App instance
 * @param controller Controller to handle
 * @param request Request to handle
 */
void app_handle_unknown_request(app_t *app, controller_t *controller,
    request_t *request);

/**
 * @brief Handle request of a graphic controller
 * @param app App instance
 * @param controller Controller to handle
 * @param request Request to handle
 */
void app_handle_graphic_request(app_t *app, controller_t *controller,
    request_t *request);

/**
 * @brief Handle request of a player controller
 * @param app App instance
 * @param controller Controller to handle
 * @param request Request to handle
 */
void app_handle_player_request(app_t *app, controller_t *controller,
    request_t *request);

/**
 * @brief Handle gui request for teams names
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_gui_request_teams_names(app_t *app, controller_t *controller,
    request_t *request);

/**
 * @brief Handle gui request for map size
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_gui_request_map_size(app_t *app, controller_t *controller,
    request_t *request);

/**
 * @brief Handle gui request for map content
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_gui_request_map_content(app_t *app, controller_t *controller,
    request_t *request);

/**
 * @brief Handle gui request for map cell content
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_gui_request_map_cell_content(app_t *app,
    controller_t *controller, request_t *request);

/**
 * @brief Handle gui request for player position
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_gui_request_player_position(app_t *app,
    controller_t *controller, request_t *request);

/**
 * @brief Handle gui request for player level
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_gui_request_player_level(app_t *app,
    controller_t *controller, request_t *request);

/**
 * @brief Handle gui request for player inventory
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_gui_request_player_inventory(app_t *app,
    controller_t *controller, request_t *request);

/**
 * @brief Handle gui request for time unit
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_gui_request_get_time_unit(app_t *app, controller_t *controller,
    request_t *request);

/**
 * @brief Handle gui request for time unit
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_gui_request_set_time_unit(app_t *app, controller_t *controller,
    request_t *request);

/**
 * @brief Handle player request for forward
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_forward_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for forward at end of cooldown
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_forward_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for right
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_turn_right_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for right at end of cooldown
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_turn_right_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for left
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_turn_left_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for left at end of cooldown
 * @param app App instance
 * @param controller Controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_turn_left_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for inventory
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_inventory_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for inventory at end of cooldown
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_inventory_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for connect_nbr
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_connect_nbr_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for connect_nbr at end of cooldown
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_connect_nbr_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for fork
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_fork_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for fork at end of cooldown
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_fork_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for take
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_take_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for take at end of cooldown
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_take_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for set
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_set_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for set at end of cooldown
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_set_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for incantation
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_incantation_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for look at end of cooldown
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_look_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for look
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_look_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for broadcast at end of cooldown
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_broadcast_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for broadcast
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_broadcast_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for eject at end of cooldown
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 */
void app_handle_player_request_eject_onfinish(app_t *app,
    player_controller_t *controller, request_t *request);

/**
 * @brief Handle player request for eject
 * @param app App instance
 * @param controller Player controller that made the request
 * @param request Request to handle
 * @return true if the cooldown can be set, false otherwise
 */
bool app_handle_player_request_eject_onstart(app_t *app,
    player_controller_t *controller, request_t *request);

/** @} */ // end of server
