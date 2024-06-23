/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#pragma once

#include <stddef.h>
#include "team.h"
#include "resource.h"
#include "types/list.h"
#include "types/vector2.h"
#include "types/controller.h"
#include "types/trantor/map.h"
#include "types/trantor/incantation.h"

// @brief Number of life units per food collected
#define PLAYER_LIFE_UNITS_PER_FOOD 1260
// @brief Default player direction
#define PLAYER_DIRECTION_DEFAULT DIR_NORTH
// @brief Player direction offset when turning left or right
#define PLAYER_DIRECTION_LEFT_OFFSET (-1)
// @brief Player direction offset when turning left or right
#define PLAYER_DIRECTION_RIGHT_OFFSET 1
// @brief Number of player directions
#define DIR_LEN 4
// @brief Generate a random player direction
#define PLAYER_RANDOM_DIRECTION() ((random() % DIR_LEN) + 1)

// @brief Structure representing a player look info
typedef struct player_look_info_s {
    // @brief Buffer size
    size_t buf_size;
    // @brief Look vector
    vector2l_t vector;
} player_look_info_t;

// @brief Structure representing a Trantorian player's direction
typedef enum player_direction_e {
    // @brief North direction
    DIR_NORTH = 1,
    // @brief East direction
    DIR_EAST,
    // @brief South direction
    DIR_SOUTH,
    // @brief West direction
    DIR_WEST
} player_direction_t;

// @brief Structure representing a Trantorian player
typedef struct player_s {
    // @brief Inventory of player resources
    size_t inventory[RES_LEN];
    // @brief Link to player team
    team_t *team;
    // @brief Link to player controller
    player_controller_t *controller;
    // @brief Number of player lives (aka the sum of collected food x 126)
    time_unit_t lives;
    // @brief Position of the player on the map
    vector2u_t position;
    // @brief Level of the player
    size_t level;
    // @brief Current player incantation
    incantation_t *incantation;
    // @brief Direction of the player
    player_direction_t direction;
    // @brief Player number
    size_t id;
} player_t;

/**
 * @brief Create a new player
 * @param id ID of the player
 * @return Created player or NULL if an error occurred
 */
player_t *player_new(size_t id);

/**
 * @brief Free a player
 * @param player Player structure to free
 */
void player_free(player_t *player);

/**
 * @brief Free a player as node data
 * @param data Player structure to free
 */
void player_free_as_node_data(node_data_t data);

/**
 * @brief Change player direction
 * @param player Player structure
 * @param direction_offset Direction offset (in degrees)
 */
void player_change_direction(player_t *player, int direction_offset);

/**
 * @brief Take an object from the current map cell at current player position
 * @param map Map to take the object from
 * @param player Player to take the object
 * @param resource Resource to take
 */
bool player_take_object(player_t *player, map_t *map, resource_t resource);

/**
 * @brief Set an object to the current map cell at current player position
 * @param player Player to set the object
 * @param map Map to set the object to
 * @param resource Resource to set
 */
bool player_set_object(player_t *player, map_t *map, resource_t resource);

/**
 * @brief Move a player forward in the world
 * @param player Player to move
 * @param map World to move the player in
 */
void player_forward(player_t *player, map_t *map);

/**
 * @brief Update player food units
 * @param player Player to update
 * @param time_units Time units to add to player lives
 */
void player_update_lives(player_t *player, time_unit_t time_units);

/**
 * @brief Set a player inventory resource
 * @param player Player to set the resource to
 * @param resource Resource to set
 * @param quantity Quantity to set
 */
bool player_set_inventory_resource(player_t *player, resource_t resource,
    int quantity);

/**
 * @brief Get the player's vision string containing all the resources
 * he can see
 * @param player Player to get the vision from
 * @param map Map to get the vision from
 * @return Vision string
 */
char *player_look(player_t *player, map_t *map);

/**
 * @brief Get the player's look vector
 * @param player Player to get the look vector from
 * @param info Look info to get the look vector from
 */
void player_get_look_vector(player_t *player, player_look_info_t *info);

/**
 * @brief Get the player's look on vertical or horizontal axis
 * @param player Player to get the look from
 * @param map Map to get the look from
 * @param info Look info to get the look fro
 * @param cell_stats Cell stats to get the look from
 */
void player_get_look_axis(player_t *player, map_t *map,
    player_look_info_t *info, map_cell_stats_t *cell_stats);
