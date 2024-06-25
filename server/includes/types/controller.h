/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** controller.h
*/

#pragma once

#include "list.h"
#include "types/request.h"
#include "types/trantor/chrono.h"
#include "types/trantor/team.h"
#include "types/trantor/map.h"
#include "types/vector2.h"
#include "buffer.h"

#define PAGE_SIZE 4096

// Forward declaration of server
typedef struct server_s server_t;

// Max number of requests a player can have
#define CTRL_PLAYER_MAX_REQ 10

// Max number of requests a generic controller can have
#define CTRL_GENERIC_MAX_REQ 3

// Average size of emission line for graphic controller
#define CTRL_GRAPHIC_AVERAGE_EMISSION_SIZE 40

// Size of emission buffer
#define CTRL_EMIT_BUFF_SIZE 4096

// Check if controller can emit data
#define CTRL_CAN_EMIT(c) ((c)->generic.state & CTRL_ALLOW_EMIT)
// Check if controller can receive requests
#define CTRL_CAN_REQ(c) ((c)->generic.state & CTRL_ALLOW_REQ)

// Forward declaration
typedef struct player_s player_t;

// @brief Controller types
typedef enum controller_type_e {
    // @brief Unknown controller
    CTRL_UNKNOWN = 1,
    // @brief Player controller
    CTRL_PLAYER = 2,
    // @brief Graphic controller
    CTRL_GRAPHIC = 4
} controller_type_t;

// @brief Controller states
typedef enum controller_read_state_e {
    // @brief Controller is disconnected
    CTRL_DISCONNECTED = 0,
    // @brief Controller is allowed to receive requests
    CTRL_ALLOW_REQ = 1,
    // @brief Controller is allowed to emit data
    CTRL_ALLOW_EMIT = 2,
    // @brief Controller is connected
    CTRL_CONNECTED = CTRL_ALLOW_EMIT | CTRL_ALLOW_REQ
} controller_state_t;

// @brief Represent a generic controller
typedef struct generic_controller_s {
    // @brief Controller socket
    int socket;
    // @brief List of pending requests
    list_t *requests;
    // @brief Buffer of data to emit to client
    buffer_t *emissions;
    // @brief Controller type
    controller_type_t type;
    // @brief Controller state
    controller_state_t state;
    // @brief Parent server
    server_t *server;
} generic_controller_t;

// @brief Represent a graphic controller
typedef generic_controller_t graphic_controller_t;

// @brief Represent a player controller
typedef struct player_controller_s {
    // @brief Controller socket
    int socket;
    // @brief List of pending requests
    list_t *requests;
    // @brief Buffer of data to emit to client
    buffer_t *emissions;
    // @brief Controller type
    controller_type_t type;
    // @brief Controller state
    controller_state_t state;
    // @brief Parent server
    server_t *server;
    // @brief Link to player instance
    player_t *player;
    // @brief Player cooldown (time units locked for)
    time_unit_t cooldown;
} player_controller_t;

// @brief Represent a controller
typedef union controller_u {
    // @brief Generic controller
    generic_controller_t generic;
    // @brief Graphic controller
    graphic_controller_t graphic;
    // @brief Player controller
    player_controller_t player;
} controller_t;

/**
 * @brief Initialize a controller.
 * This function set controller type to CTRL_UNKNOWN.
 * @param controller Controller to initialize
 * @param socket Socket to attach to the controller
 */
void controller_init(controller_t *controller, int socket);

/**
 * @brief Create a new controller
 * @param socket Socket to attach to the controller
 * @return Created controller or NULL if an error occurred
 */
controller_t *controller_new(int socket);

/**
 * @brief Free a controller
 * @param controller Controller to free
 */
void controller_free(controller_t *controller);

/**
 * @brief Free a controller
 * @param data Node data to free as controller
 */
void controller_free_as_node_data(node_data_t data);

/**
 * @brief Emit as much emissions as possible of the controller
 * @param controller Controller to emit
 * @return true if the controller emitted, false otherwise
 */
bool controller_emit(controller_t *controller);

/**
 * @brief Try to emit current buffer of a controller
 * @param controller Controller to emit
 * @return true if the controller emitted, false otherwise
 */
bool controller_try_emit(controller_t *controller);

/**
 * @brief Add an emission to the controller from a format
 * @param controller Controller to add the emission to
 * @param format Format string as in printf
 * @param ... Arguments for the format string
 * @return true if the emission was added, false otherwise
 */
bool controller_add_emission(controller_t *controller,
    char *format, ...) __attribute__((format(printf, 2, 3)));

/**
 * @brief Add an emission to the controller from a raw content
 * @param controller Controller to add the emission to
 * @param content Content to add
 * @param size Size of the content
 * @return true if the emission was totally added, false otherwise
 */
bool controller_add_emission_raw(controller_t *controller,
    const char *content, size_t size);

/**
 * @brief Add an emission to types controllers matching types in a list
 * @param controllers List of controllers
 * @param types Types of controllers to add emission to
 * @param format Format string as in printf
 * @param ... Arguments for the format string
 * @return true if the emission was added, false otherwise
 */
bool controllers_add_emission(list_t *controllers,
    controller_type_t types, char *format, ...)
__attribute__((format(printf, 3, 4)));

/**
 * @brief Add an emission to types controllers matching types in a list
 * @param controllers Controllers list
 * @param types Types of controllers to add emission to
 * @param content Content to add
 * @param size Size of the content
 * @return true if the emission was added, false otherwise
 */
bool controllers_add_emission_raw(list_t *controllers,
    controller_type_t types, const char *content, size_t size);

/**
 * @brief Get next pending request of a controller
 * @param controller Controller to get request from
 * @return Next pending request or NULL if an error occurred or
 * max request policy reached
 */
request_t *controller_get_next_pending_request(controller_t *controller);

/**
 * @brief Read pending data from a controller and transform it into requests
 * @param controller Controller to read from
 * @return Controller state after reading
 */
controller_state_t controller_read(controller_t *controller);

/**
 * @brief Get last request of a controller
 * @param controller Controller to get request from
 * @return Last request or NULL if no request
 */
request_t *controller_get_last_request(controller_t *controller);

/**
 * @brief Clear first request of a controller
 * @param controller Controller to clear first request from
 */
void controller_clear_first_request(controller_t *controller);

/**
 * @brief Read next token from a buffer
 * @param start Start of the buffer
 * @param size Size of the buffer
 * @param token Token to fill
 * @return true if is the last token, false otherwise
 */
bool controller_read_next_token(char *start, size_t size,
    request_token_t *token);

/**
 * @brief Handle a token from a buffer
 * @param controller Controller to handle token
 * @param token Token to handle
 */
void controller_handle_buffer_token(controller_t *controller,
    request_token_t *token);

/**
 * @brief Handle a buffer from a controller and append it to
 * controller requests
 * @param controller Controller to handle buffer
 * @param buffer Buffer to handle
 * @param size Size of the buffer
 */
void controller_handle_buffer(controller_t *controller,
    char buffer[REQ_BUFF_SIZE], size_t size);

/**
 * @brief Initialize a player controller from a generic controller
 * @param controller Controller to initialize
 * @param player Player to link to the controller
 * @return true if the controller was initialized, false otherwise
 */
bool controller_player_from_generic(controller_t *controller,
    player_t *player);

/**
 * @brief Initialize a graphic controller from a generic controller
 * @param controller Controller to initialize
 * @param map Map to use to dynamically allocate buffer
 * @return true if the controller was initialized, false otherwise
 */
bool controller_graphic_from_generic(controller_t *controller, map_t *map);

/**
 * @brief Check if a controller can emit data
 * @param controller Controller to check
 * @return Emission possibility
 */
bool controller_can_receive(controller_t *controller);

/**
 * @brief Check if a controller has content to read
 * @param controller Controller to check
 * @return Read possibility
 */
bool controller_has_content_to_read(controller_t *controller);

/**
 * @brief Clear all requests of a controller
 * @param controller Controller to clear requests from
 */
void controller_clear_requests(controller_t *controller);
