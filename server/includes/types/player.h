/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#pragma once

#include <stddef.h>
#include "list.h"
#include "team.h"
#include "resource.h"

// TODO: remove once the player controller is implemented
typedef float player_controller_t;

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
} player_t;

/**
 * @brief Create a new player
 * @param controller Player controller
 * @param team Player team
 * @param position Player position
 * @return
 */
player_t *player_new(player_controller_t *controller, team_t *team,
                     vector2u_t position);

