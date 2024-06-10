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
#include "resources.h"

// TODO: rmeove
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

// @brief Structure representing a Trantorian egg
typedef struct egg_s {
    // @brief Identifier of the egg
    size_t id;
    // @brief Position of the egg on the map
    vector2u_t position;
    // @brief Link to the team that laid the egg
    team_t *team;
} egg_t;
