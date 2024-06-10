/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#pragma once

#include <stddef.h>
#include "list.h"

typedef struct team_s {
    list_t *players;
    char *name;
    list_t *eggs;
    size_t min_slots;
} team_t;
