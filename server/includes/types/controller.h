/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** controller.h
*/

#pragma once

#include "list.h"

// TODO: Temporary player definition
typedef void * player_t;

// TODO: Temporary time_unit definition
typedef void * time_unit_t;

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
