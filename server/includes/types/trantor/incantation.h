/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** incantation.h
*/

#pragma once

#include "types/list.h"
#include "types/controller.h"
#include "map.h"

typedef struct world_s world_t;

// @brief Duration of an incantation
#define INCANTATION_DURATION 300

// @brief Structure representing the requirements for an incantation
typedef struct incantation_requirements_s {
    // @brief Number of players with the same level required
    size_t nb_players;
    // @brief Resources required for the incantation
    size_t resources[RES_LEN];
} incantation_requirements_t;

// @brief Represents a world incantation
typedef struct incantation_s {
    // @brief List of players involved in the incantation
    list_t *players;
    // @brief Incantation cooldown
    time_unit_t cooldown;
    // @brief Requester
    player_t *requester;
    // @brief The level of the incantation
    unsigned int level;
} incantation_t;

/**
 * @brief Create a new incantation
 * @param cell Cell on which the incantation is happening
 * @param level Desired level of the incantation
 * @return Created incantation or NULL if failed
 */
incantation_t *incantation_new(unsigned int level);

/**
* @brief Free given incantation
* @param incantation Incantation to free
*/
void incantation_free(incantation_t *incantation);

/**
 * @brief Add a player to the incantation
 * @param incantation Incantation to add the player to
 * @param player Player to add to the incantation
 */
void incantation_remove_player(incantation_t *incantation, player_t *player);

/**
 * @brief Remove all players from the incantation
 * @param incantation Incantation to remove all players from
 */
void incantation_remove_all_players(incantation_t *incantation);

/**
 * @brief Add a player to the incantation
 * @param incantation Incantation to add the player to
 * @param player Player to add to the incantation
 * @return true if the player was added, false otherwise
 */
bool incantation_add_player(incantation_t *incantation, player_t *player);

/**
 * @brief Free given incantation as node data
 * @param incantation Incantation to free as node data
 */
void incantation_free_as_node_data(node_data_t incantation);

/**
 * @brief Check if an incantation is valid
 * @param incantation Incantation to check
 * @param map Map of the world
 * @return Incantation is valid or not
 */
bool incantation_is_valid(incantation_t *incantation, map_t *map);

/**
 * @brief Get the incantation requirements for a given level
 * @param level Level of the incantation
 * @return The incantation requirements
 */
incantation_requirements_t *incantation_get_requirements(unsigned int level);

/**
 * @brief Complete a successful incantation
 * @param incantation Incantation to complete
 * @param map Map of the world
 */
bool incantation_complete_success(incantation_t *incantation,
    map_t *map);

/**
 * @brief Add players from a cell to an incantation
 * @param incantation Incantation to add players to
 * @param cell Cell to get players from
 * @return true is all players has been added, false otherwise
 */
bool incantation_add_players_from_cell(incantation_t *incantation,
    map_cell_t *cell);
