/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** World
*/

#pragma once

#include <stddef.h>
#include "chrono.h"
#include "../list.h"
#include "resource.h"

// @brief Structure representing a Trantorian map cell
typedef struct map_cell_s {
    // @brief List of players references currently on the cell
    list_t *players;
    // @brief List of resources on the cell
    size_t resources[RES_LEN];
    // @brief List of eggs on the cell
    list_t *eggs;
} map_cell_t;

// @brief Structure representing a Trantorian map
typedef struct map_s {
    // @brief Size of the map
    vector2u_t size;
    // @brief Cells of the map
    map_cell_t **cells;
} map_t;

// @brief Structure representing a Trantorian world
typedef struct world_s {
    // @brief Map of the world
    map_t *map;
    // @brief List of teams in the world
    list_t *teams;
    // @brief List of players in the world
    list_t *players;
    // @brief Clock of the world
    chrono_t clock;
    // @brief Resources manager of the world
    resource_manager_t *resources_manager;
    // @brief Delay before next predictable event in world
    time_unit_t next_event_delay;
    // @brief List of incantations in the world
    list_t *incantations;
} world_t;

/**
 * @brief Create a new trantorian world
 * @param width Width of the world
 * @param height Height of the world
 * @param frequency Frequency of the world clock
 * @return world structure
 */
world_t *world_new(int width, int height, float frequency);

// TODO : Add free of incantations list in the world free function
/**
 * @brief Free a trantorian world
 * @param world
 */
void world_free(world_t *world);