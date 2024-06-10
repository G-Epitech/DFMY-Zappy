/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#pragma once

#include <stddef.h>
#include "list.h"

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
