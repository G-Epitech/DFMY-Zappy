/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** stats.c
*/

#include <memory.h>
#include "types/trantor/map.h"

void map_cell_get_stats(map_cell_t *cell, map_cell_stats_t *stats)
{
    memccpy(stats->resources, cell->resources, RES_LEN,
            sizeof(size_t) * RES_LEN);
    stats->players = cell->players->len;
    stats->eggs = cell->eggs->len;
}
