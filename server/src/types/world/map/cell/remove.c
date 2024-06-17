/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** remove.c
*/

#include "types/world/map.h"
#include "types/world/resource.h"

void map_cell_remove_resource(map_cell_t *cell, resource_t resource,
    size_t quantity)
{
    if (!cell)
        return;
    cell->resources[resource] -= quantity;
}
