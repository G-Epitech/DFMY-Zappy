/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/map.h"
#include "types/world/player.h"

void map_add_resource(map_t *map, vector2u_t pos, resource_t resource,
    size_t quantity)
{
    if (!map)
        return;
    map->cells[pos.y][pos.x].resources[resource] += quantity;
}

bool map_add_player(map_t *map, player_t *player)
{
    vector2u_t position;

    if (!map)
        return false;
    vector2u_random(&position, &map->size);
    if (!list_push(map->cells[position.y][position.x].players,
        NODE_DATA_FROM_PTR(player)
    )) {
        return false;
    }
    player->position = position;
    return true;
}
