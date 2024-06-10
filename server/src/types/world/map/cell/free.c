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
    if (cell->players)
        list_free(cell->players, NULL);
    if (cell->eggs)
        list_free(cell->eggs, NULL);
}
