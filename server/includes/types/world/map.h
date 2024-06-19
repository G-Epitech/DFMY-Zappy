/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map.h
*/

#pragma once

#include "types/list.h"
#include "types/vector2.h"
#include "types/world/resource.h"

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

/**
 * @brief Create a new map
 * @param size Size of the map
 * @return Created map or NULL if an error occurred
 */
map_t *map_new(vector2u_t size);

/**
 * @brief Free given map
 * @param map Map to free
 */
void map_free(map_t *map);

/**
 * @brief Initialize given map cell
 * @param cell Cell to initialize
 * @return Success status of the operation
 */
bool map_cell_init(map_cell_t *cell);

/**
 * @brief Free given map cell
 * @param cell Cell to free
 */
void map_cell_free(map_cell_t *cell);

/**
 * @brief Add a resource to the current map cell
 * @param map Map to add the resource to
 * @param pos Position of the cell to add the resource to
 * @param resource Resource to add
 * @param quantity Quantity of the resource to add
 */
void map_add_resource(map_t *map, vector2u_t pos, resource_t resource,
    size_t quantity);

/**
 * @brief Remove a resource from the current map cell
 * @param map Map to remove the resource from
 * @param pos Position of the cell to remove the resource from
 * @param resource Resource to remove
 * @param quantity Quantity of the resource to remove
 */
void map_remove_resource(map_t *map, vector2u_t pos, resource_t resource,
    size_t quantity);

/**
 * @brief Resolve a position on the map
 * @param pos Position to resolve
 * @param map Size of the map
 * @return Resolved position
 */
vector2u_t map_resolve_position(map_t *map, vector2l_t pos);
