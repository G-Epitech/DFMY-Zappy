/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** take.c
*/

#include "types/trantor/player.h"
#include "types/trantor/map.h"
#include "types/trantor/resource.h"

bool player_take_object(map_t *map, player_t *player, resource_t resource)
{
    map_cell_t *cell = NULL;

    if (!map || !player)
        return false;
    cell = &map->cells[player->position.y][player->position.x];
    if (cell->resources[resource] > 0) {
        player_set_inventory_resource(player, resource, 1);
        cell->resources[resource] -= 1;
        return true;
    }
    return false;
}
