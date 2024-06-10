/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Resources
*/

#pragma once

#include <stddef.h>
#include "clock.h"

typedef enum resource_e {
    RES_FOOD,
    RES_LINEMATE,
    RES_DERAUMERE,
    RES_SIBUR,
    RES_MENDIANE,
    RES_PHIRAS,
    RES_THYSTAME,
    RES_LEN
} resource_t;

typedef struct resource_stat_s {
    size_t actual;
    size_t limit;
} resource_stat_t;

typedef struct resource_manager_s {
    resource_stat_t stats[RES_LEN];
    time_unit_t next_generation;
} resource_manager_t;
