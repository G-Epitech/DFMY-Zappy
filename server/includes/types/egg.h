/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Egg
*/

#pragma once

#include <stddef.h>
#include "team.h"

// @brief Structure representing a Trantorian egg
typedef struct egg_s {
    // @brief Identifier of the egg
    size_t id;
    // @brief Position of the egg on the map
    vector2u_t position;
    // @brief Link to the team that laid the egg
    team_t *team;
} egg_t;

egg_t *egg_new(team_t *team, vector2u_t position);
