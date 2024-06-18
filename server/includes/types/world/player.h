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
#include "incantation.h"

// @brief Number of life units per food collected
#define PLAYER_LIFE_UNITS_PER_FOOD 126

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
    // @brief Current player incantation
    incantation_t *incantation;
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
