/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** World
*/

#pragma once

#include <stddef.h>
#include "map.h"
#include "chrono.h"
#include "resource.h"
#include "types/list.h"

// @brief Structure representing a Trantorian world
typedef struct world_s {
    // @brief Map of the world
    map_t *map;
    // @brief List of teams in the world
    list_t *teams;
    // @brief List of players in the world
    list_t *players;
    // @brief Clock of the world
    chrono_t chrono;
    // @brief Resources manager of the world
    resources_manager_t resources_manager;
    // @brief Delay before next predictable event in world
    time_unit_t next_event_delay;
    // @brief List of incantations in the world
    list_t *incantations;
} world_t;

/**
 * @brief Create a new trantorian world
 * @param map_size Size of the world map
 * @param frequency Frequency of the world clock
 * @return world structure
 */
world_t *world_new(vector2u_t map_size, size_t frequency);

/**
 * @brief Free a trantorian world
 * @param world World to free
 */
void world_free(world_t *world);

/**
 * @brief Check the delay of the next event to see if it needs to be updated
 * @param world World to check
 * @param event_delay Delay of the event to check
 */
void world_register_event(world_t *world, time_unit_t event_delay);
