/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#pragma once

#include <stddef.h>
#include "../list.h"

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
 * @return team structure
 */
team_t *team_new(char *name, size_t min_slots);

/**
 * @brief Free a team
 * @param team The team to free
 */
void team_free(team_t *team);

/**
 * @brief Free a team as node data
 * @param data The team to free
 */
void team_free_as_node_data(void *data);
