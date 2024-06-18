/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** take.c
*/

#include "types/world/player.h"
#include "types/world/map.h"
#include "types/world/resource.h"

bool player_set_object(map_t *map, player_t *player, resource_t resource)
{
    map_cell_t *cell = NULL;

    if (!map || !player)
        return false;
    cell = &map->cells[player->position.y][player->position.x];
    if (player_set_inventory_resource(player, resource, -1)) {
        cell->resources[resource] += 1;
        return true;
    }
    return false;
}
