/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/trantor/map.h"

void map_remove_resource(map_t *map, vector2u_t pos, resource_t resource,
    size_t quantity)
{
    if (!map || map->cells[pos.y][pos.x].resources[resource] == 0)
        return;
    map->cells[pos.y][pos.x].resources[resource] -= quantity;
}
