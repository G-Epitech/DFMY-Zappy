/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/map.h"

void map_add_resource(map_t *map, vector2u_t pos, resource_t resource,
    size_t quantity)
{
    if (!map)
        return;
    map->cells[pos.y][pos.x].resources[resource] += quantity;
}
