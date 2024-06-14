/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** controller.h
*/

#pragma once

#include "list.h"
#include "types/request.h"
#include "types/world/chrono.h"

// Max size of a request buffer
#define CTRL_MAX_REQ_SIZE (10 * REQ_BUFF_SIZE)

// Max number of requests a player can have
#define CTRL_PLAYER_MAX_REQ 10

// Forward declaration
typedef struct player_s player_t;

// Frozen state of a player
typedef enum frozen_state_e {
    // @brief Not frozen
    FROZ_NO,
    // @brief Frozen by himself
    FROZ_HIMSELF,
    // @brief Frozen by another player
    FROZ_BY_OTHER
} frozen_state_t;

// @brief Controller types
typedef enum controller_type_e {
    // @brief Unknown controller
    CTRL_UNKNOWN,
    // @brief Player controller
    CTRL_PLAYER,
    // @brief Graphic controller
    CTRL_GRAPHIC
} controller_type_t;

// @brief Controller states
typedef enum controller_read_state_e {
    // @brief Controller is connected
    CTRL_CONNECTED,
    // @brief Controller is disconnected
    CTRL_DISCONNECTED,
} controller_state_t;

// @brief Represent a generic controller
typedef struct generic_controller_s {
    // @brief Controller socket
    int socket;
    // @brief List of pending requests
    list_t *requests;
    // @brief List of pending emissions
    list_t *emissions;
    // @brief Controller type
    controller_type_t type;
} generic_controller_t;

// @brief Represent a graphic controller
typedef generic_controller_t graphic_controller_t;

// @brief Represent a player controller
typedef struct player_controller_s {
    // @brief Controller socket
    int socket;
    // @brief Requests that the player made
    list_t *requests;
    // @brief List of data to emit to client
    list_t *emissions;
    // @brief Controller type
    controller_type_t type;
    // @brief Link to player instance
    player_t *player;
    // @brief Player cooldown (time units locked for)
    time_unit_t cooldown;
    // @brief Specify if the player is frozen by an incantation
    frozen_state_t frozen;
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

