/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/map.h"

static void map_free_cells(map_t *map)
{
    for (int i = 0; i < map->size.y; i++) {
        for (int j = 0; j < map->size.x; j++) {
            map_cell_free(&(map->cells[i][j]));
        }
        free(map->cells[i]);
    }
}

void map_free(map_t *map)
{
    if (!map || !map->cells)
        return;
    map_free_cells(map);
    free(map);
}
