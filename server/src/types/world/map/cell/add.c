/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** add.c
*/

#include "types/world/map.h"
#include "types/world/resource.h"

void map_cell_add_resource(map_cell_t *cell, resource_t resource,
    size_t quantity)
{
    if (!cell)
        return;
    cell->resources[resource] += quantity;
}
