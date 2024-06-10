/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#pragma once

#include <stddef.h>
#include "list.h"
#include "team.h"
#include "resources.h"

// TODO: rmeove
typedef float player_controller_t;


typedef struct player_s {
    size_t inventory[RES_LEN];
    team_t *team;
    player_controller_t *controller;
    float lives;
    vector2u_t position;
    size_t level;
} player_t;

typedef struct egg_s {
    size_t id;
    vector2u_t position;
    team_t *team;
} egg_t;
