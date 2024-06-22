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
    unsigned long id;
    // @brief Position of the egg on the map
    vector2u_t position;
    // @brief Link to the team that laid the egg
    team_t *team;
    // @brief ID of the player that laid the egg
    long laid_by;
} egg_t;

/**
 * @brief Initialize an egg
 * @param egg Egg to initialize
 * @param laid_by ID of the player that laid the egg
 * @param id ID of the egg
 */
void egg_init(egg_t *egg, long laid_by, size_t id);

/**
 * @brief Create a new egg
 * @param laid_by ID of the player that laid the egg
 * @param id ID of the egg
 * @return A pointer to the newly created egg
 */
egg_t *egg_new(long laid_by, size_t id);

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
