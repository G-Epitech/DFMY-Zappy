/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#pragma once

#include <stddef.h>
#include "types/list.h"

// Forward player declaration
typedef struct player_s player_t;

// Forward egg declaration*
typedef struct egg_s egg_t;

// @brief Structure representing a Trantorian team
typedef struct team_s {
    // @brief List of players references in the team
    list_t *players;
    // @brief Name of the team
    char *name;
    // @brief List of eggs on the team
    list_t *eggs;
    // @brief Minimum number of slots in the team
    size_t min_slots;
} team_t;

/**
 * @brief Create a new team
 * @param name Name of the team
 * @param min_slots Minimum number of slots in the team
 * @return Created team or NULL if an error occurred
 */
team_t *team_new(char *name, size_t min_slots);

/**
 * @brief Add a player to the team
 * @param team The team to add the player to
 * @param player The player to add to the team
 * @return true if the player was added, false otherwise
 */
bool team_add_player(team_t *team, player_t *player);

/**
 * @brief Remove a player from the team
 * @param team The team to remove the player from
 * @param player Player to remove from the team
 */
void team_remove_player(team_t *team, player_t *player);

/**
 * @brief Add an egg to the team
 * @param team The team to add the egg to
 * @param egg The egg to add to the team
 * @return true if the egg was added, false otherwise
 */
bool team_add_egg(team_t *team, egg_t *egg);

/**
 * @brief Remove an egg from the team
 * @param team The team to remove the egg from
 * @param egg The egg to remove from the team
 */
void team_remove_egg(team_t *team, egg_t *egg);

/**
 * @brief Free a team
 * @param team The team to free
 */
void team_free(team_t *team);

/**
 * @brief Free a team as node data
 * @param data The team to free
 */
void team_free_as_node_data(node_data_t data);
