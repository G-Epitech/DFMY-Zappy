/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#pragma once

#include <stddef.h>
#include "team.h"
#include "resource.h"
#include "types/list.h"
#include "types/vector2.h"
#include "types/controller.h"

// @brief Number of life units per food collected
#define PLAYER_LIFE_UNITS_PER_FOOD 126

// @brief Default player direction
#define PLAYER_DIRECTION_DEFAULT DIR_NORTH
// @brief Player direction offset when turning left or right
#define PLAYER_DIRECTION_LEFT_OFFSET (-1)
// @brief Player direction offset when turning left or right
#define PLAYER_DIRECTION_RIGHT_OFFSET 1

// @brief Structure representing a Trantorian player's direction
typedef enum player_direction_e {
    // @brief North direction
    DIR_NORTH = 1,
    // @brief East direction
    DIR_EAST,
    // @brief South direction
    DIR_SOUTH,
    // @brief West direction
    DIR_WEST
} player_direction_t;

// @brief Structure representing a Trantorian player
typedef struct player_s {
    // @brief Inventory of player resources
    size_t inventory[RES_LEN];
    // @brief Link to player team
    team_t *team;
    // @brief Link to player controller
    player_controller_t *controller;
    // @brief Number of player lives (aka the sum of collected food x 126)
    float lives;
    // @brief Position of the player on the map
    vector2u_t position;
    // @brief Level of the player
    size_t level;
    // @brief Direction of the player
    player_direction_t direction;
    // @brief Player number
    size_t number;
} player_t;

/**
 * @brief Create a new player
 * @param controller Player controller
 * @param team Player team
 * @param position Player position
 * @return Created player or NULL if an error occurred
 */
player_t *player_new(player_controller_t *controller, team_t *team,
    vector2u_t position);

/**
 * @brief Free a player
 * @param player Player structure to free
 */
void player_free(player_t *player);

/**
 * @brief Free a player as node data
 * @param data Player structure to free
 */
void player_free_as_node_data(node_data_t data);

/**
 * @brief Change player direction
 * @param player Player structure
 * @param direction_offset Direction offset (in degrees)
 */
void player_change_direction(player_t *player, int direction_offset);
