/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/map.h"

void map_cell_free(map_cell_t *cell)
{
    if (!cell)
        return;
    list_free(cell->players, NULL);
    list_free(cell->eggs, NULL);
}
