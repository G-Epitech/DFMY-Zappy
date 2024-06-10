/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/map.h"

static bool map_create_rows_cells(map_cell_t **cells, vector2u_t size)
{
    for (int i = 0; i < size.y; i++) {
        cells[i] = calloc(size.x, sizeof(map_cell_t));
        if (!cells[i]) {
            return false;
        }
    }
    return true;
}

map_t *map_new(vector2u_t size)
{
    map_t *map = calloc(1, sizeof(map_t));

    if (!map)
        return NULL;
    map->size = size;
    map->cells = calloc(size.y, sizeof(map_cell_t *));
    if (!map->cells || !map_create_rows_cells(map->cells, size)) {
        free(map);
        return NULL;
    }
    return map;
}
