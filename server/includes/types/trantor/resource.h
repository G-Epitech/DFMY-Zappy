/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Resources
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "chrono.h"
#include "types/vector2.h"

// @brief Default next generation delay
#define RES_MANAGER_NEXT_GENERATION_DELAY 20

// @brief Imprecision limit for resource generation
#define RES_LIMIT_IMPRECISION 1e-3f

// @brief Density of food
#define RES_FOOD_DENSITY 0.5f

// @brief Density of linemate resource
#define RES_LINEMATE_DENSITY 0.3f

// @brief Density of deraumere resource
#define RES_DERAUMERE_DENSITY 0.15f

// @brief Density of sibur resource
#define RES_SIBUR_DENSITY 0.1f

// @brief Density of mendiane resource
#define RES_MENDIANE_DENSITY 0.1f

// @brief Density of phiras resource
#define RES_PHIRAS_DENSITY 0.08f

// @brief Density of thystame resource
#define RES_THYSTAME_DENSITY 0.05f

// @brief The enum representing the type of resource
typedef enum resource_e {
    // @brief Food resource
    RES_FOOD,
    // @brief Linemate resource
    RES_LINEMATE,
    // @brief Deraumere resource
    RES_DERAUMERE,
    // @brief Sibur resource
    RES_SIBUR,
    // @brief Mendiane resource
    RES_MENDIANE,
    // @brief Phiras resource
    RES_PHIRAS,
    // @brief Thystame resource
    RES_THYSTAME,
    // @brief Number of resources
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

/**
 * @brief Get resource from string
 * @param resource Pointer to store the resource
 * @param str String to convert
 * @return True if the conversion was found, false otherwise
 */
bool resource_from_string(resource_t *resource, const char *str);

/**
 * @brief Get the pointer to the resource string
 * @param resource Resource to get the string from
 * @return Pointer to the resource string
 */
const char *resource_to_string(resource_t resource);

/**
 * @brief Get the length of a resource string
 * @param resource Resource to get the length from
 * @return Length of the resource string
 */
size_t resource_string_len(resource_t resource);
