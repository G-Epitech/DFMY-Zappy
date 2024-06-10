/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Resources
*/

#pragma once

#include <stddef.h>
#include "chrono.h"

// @brief The enum representing the type of resource
typedef enum resource_e {
    RES_FOOD,
    RES_LINEMATE,
    RES_DERAUMERE,
    RES_SIBUR,
    RES_MENDIANE,
    RES_PHIRAS,
    RES_THYSTAME,
    RES_LEN
} resource_t;

// @brief Represent statistics of a resource type
typedef struct resource_stat_s {
    // @brief Actual quantity of current resource on map
    size_t actual;
    // @brief Minimal limit of quantity needed on map
    size_t limit;
} resource_stat_t;

// @brief Represent all data relative to Trantor resources management
typedef struct resource_manager_s {
    // @brief Statistics of resources in the world
    resource_stat_t stats[RES_LEN];
    // @brief Time before next generation of resources
    time_unit_t next_generation;
} resource_manager_t;

/**
 * @brief Create a new resource manager
 * @return resource manager
 */
resource_manager_t *resource_manager_new(void);
