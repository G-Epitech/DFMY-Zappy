/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/trantor/map.h"

static void map_free_cells(map_t *map)
{
    if (!map->cells)
        return;
    for (int i = 0; i < map->size.y; i++) {
        if (!map->cells[i])
            continue;
        for (int j = 0; j < map->size.x; j++) {
            map_cell_free(&(map->cells[i][j]));
        }
        free(map->cells[i]);
    }
}

void map_free(map_t *map)
{
    if (!map)
        return;
    map_free_cells(map);
    free(map);
}
