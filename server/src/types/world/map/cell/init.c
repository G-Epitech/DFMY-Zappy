/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <memory.h>
#include "types/world/map.h"
#include "types/world/resource.h"

bool map_cell_init(map_cell_t *cell)
{
    cell->eggs = list_new();
    cell->players = list_new();
    if (!cell->eggs || !cell->players) {
        map_cell_free(cell);
        return false;
    }
    memset(cell->resources, 0, RES_LEN * sizeof(size_t));
    return true;
}
