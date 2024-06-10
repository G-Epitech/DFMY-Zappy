/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Resources
*/

#pragma once

#include <stddef.h>
#include "chrono.h"
#include "types/vector2.h"

// @brief Default next generation delay
#define RES_MANAGER_NEXT_GENERATION_DELAY 20

#define RES_MANAGER_SET_LIM(m, r) ()


#define RES_FOOD_DENSITY 0.5f
#define RES_LINEMATE_DENSITY 0.3f
#define RES_DERAUMERE_DENSITY 0.15f
#define RES_SIBUR_DENSITY 0.1f
#define RES_MENDIANE_DENSITY 0.1f
#define RES_PHIRAS_DENSITY 0.08f
#define RES_THYSTAME_DENSITY 0.05f

#define RES

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
typedef struct resources_manager_s {
    // @brief Statistics of resources in the world
    resource_stat_t stats[RES_LEN];
    // @brief Time before next generation of resources
    time_unit_t next_generation;
} resources_manager_t;

/**
 * @brief Initialize a resources manager
 * @param manager Resources manager to initialize
 * @param map_size Size of the map to compute resources proportions
 */
void resources_manager_init(resources_manager_t *manager,
    vector2u_t map_size);
