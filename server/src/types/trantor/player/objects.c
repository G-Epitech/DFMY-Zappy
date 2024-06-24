/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** take.c
*/

#include "types/trantor/player.h"
#include "types/trantor/map.h"
#include "types/trantor/resource.h"

bool player_take_object(player_t *player, map_t *map, resource_t resource)
{
    map_cell_t *cell = NULL;

    if (!map || !player)
        return false;
    cell = &map->cells[player->position.y][player->position.x];
    if (cell->resources[resource] > 0) {
        player_set_inventory_resource(player, resource, 1);
        map_remove_resource(map, player->position, resource, 1);
        return true;
    }
    return false;
}

bool player_set_object(player_t *player, map_t *map, resource_t resource)
{
    if (!map || !player)
        return false;
    if (player_set_inventory_resource(player, resource, -1)) {
        map_add_resource(map, player->position, resource, 1);
        return true;
    }
    return false;
}
