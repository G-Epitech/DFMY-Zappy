/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/trantor/map.h"

static bool map_init_row_cells(map_cell_t *cell_row, vector2u_t size)
{
    for (int i = 0; i < size.x; i++) {
        if (!map_cell_init(&cell_row[i])) {
            return false;
        }
    }
    return true;
}

static bool map_create_rows(map_cell_t **cells, vector2u_t size)
{
    if (!cells)
        return false;
    for (int i = 0; i < size.y; i++) {
        cells[i] = calloc(size.x, sizeof(map_cell_t));
        if (!cells[i] || !map_init_row_cells(cells[i], size)) {
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
    if (!map_create_rows(map->cells, size)) {
        map_free(map);
        return NULL;
    }
    return map;
}
