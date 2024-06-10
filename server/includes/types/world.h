/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** World
*/

#pragma once

#include <stddef.h>
#include "clock.h"
#include "list.h"
#include "resources.h"

typedef struct map_cell_s {
    list_t *players;
    size_t resources[RES_LEN];
    list_t *eggs;
} map_cell_t;

typedef struct map_s {
    vector2u_t size;
    map_cell_t **cells;
} map_t;

typedef struct world_s {
    map_t *map;
    list_t *teams;
    list_t *players;
    clock_t clock;
    resource_manager_t *resources_manager;
    time_unit_t next_event_delay;
    list_t *incantations;
} world_t;
