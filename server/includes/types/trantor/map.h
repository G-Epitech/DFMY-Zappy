/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map.h
*/

#pragma once

#include "types/list.h"
#include "types/vector2.h"
#include "types/trantor/resource.h"

// Forward declaration of player_t
typedef struct player_s player_t;

// Forward declaration of egg_t
typedef struct egg_s egg_t;

// @brief Get the map cell at given position
#define MAP_CELL_AT_POS(map, pos) (&(map->cells[pos.y][pos.x]))

// @brief Map player cell accessor
#define MAP_PLAYER_CELL(m, p) MAP_CELL_AT_POS(m, p->position)

// @brief Map egg cell accessor
#define MAP_EGG_CELL(m, e) MAP_CELL_AT_POS(m, e->position)

// @brief Look for position out of map
#define MAP_OUT_POSITION(m, p) ((p).x >= m->size.x || (p).y >= m->size.y)

// @brief Structure representing map cell statistics, mainly used for
// the vision functionality
typedef struct map_cell_stats_s {
    // @brief Resources on the cell
    size_t resources[RES_LEN];
    // @brief Number of players on the cell
    size_t players;
    // @brief Number of eggs on the cell
    size_t eggs;
} map_cell_stats_t;

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
 * @brief Add a player to the current to a random map cell
 * @param map Map to add the player to
 * @param player Player to add
 * @return true if the player was added, false otherwise
 */
bool map_add_player(map_t *map, player_t *player);

/**
 * @brief Remove a player from the current map cell
 * @param map Map to remove the player from
 * @param player Player to remove
 */
void map_remove_player(map_t *map, player_t *player);

/**
 * @brief Add an egg to the current to a random map cell
 * @param map Map to add the egg to
 * @param egg Egg to add
 * @return true if the egg was added, false otherwise
 */
bool map_add_egg(map_t *map, egg_t *egg);

/**
 * @brief Remove an egg from the current map cell
 * @param map Map to remove the egg from
 * @param egg Egg to remove
 */
void map_remove_egg(map_t *map, egg_t *egg);

/**
 * @brief Resolve a position on the map
 * @param pos Position to resolve
 * @param map Size of the map
 * @return Resolved position
 */
vector2u_t map_resolve_position(map_t *map, vector2l_t pos);

/**
 * @brief Get the stats of a cell
 * @param cell Cell to get the stats from
 * @param stats Stats to fill
 */
void map_cell_get_stats(map_cell_t *cell, map_cell_stats_t *stats);