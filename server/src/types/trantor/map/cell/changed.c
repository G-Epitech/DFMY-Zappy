/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/trantor/map.h"

void map_mark_cell_as_changed(map_t *map, map_cell_t *cell)
{
    if (!cell->changed)
        map->cells_changed += 1;
    cell->changed = true;
}

void map_mark_cell_as_up_to_date(map_t *map, map_cell_t *cell)
{
    if (cell->changed)
        map->cells_changed -= 1;
    cell->changed = false;
}
