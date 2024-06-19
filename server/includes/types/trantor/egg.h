/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Egg
*/

#pragma once

#include <stddef.h>
#include "team.h"
#include "types/vector2.h"

// @brief Structure representing a Trantorian egg
typedef struct egg_s {
    // @brief Identifier of the egg
    size_t id;
    // @brief Position of the egg on the map
    vector2u_t position;
    // @brief Link to the team that laid the egg
    team_t *team;
} egg_t;

/**
 * @brief Initialize an egg
 * @param egg Egg to initialize
 * @param team Team to link to the egg
 * @param position Position of the egg on the map
 */
void egg_init(egg_t *egg, team_t *team, vector2u_t position);

/**
 * @brief Create a new egg
 * @param team The team that laid the egg
 * @param position The position of the egg on the map
 * @return A pointer to the newly created egg
 */
egg_t *egg_new(team_t *team, vector2u_t position);

/**
 * @brief Free an egg
 * @param egg The egg to free
 */
void egg_free(egg_t *egg);

/**
 * @brief Free an egg as node data
 * @param data The egg to free
 */
void egg_free_as_node_data(node_data_t data);
