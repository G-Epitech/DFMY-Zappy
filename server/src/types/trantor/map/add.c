/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/trantor/egg.h"
#include "types/trantor/map.h"
#include "types/trantor/player.h"
#include "log.h"

bool map_add_resource(map_t *map, vector2u_t pos, resource_t resource,
    size_t quantity)
{
    if (!map)
        return false;
    map->cells[pos.y][pos.x].resources[resource] += quantity;
    map_mark_cell_as_changed(map, MAP_CELL_AT_POS(map, pos));
    map->resources_manager.stats[resource].actual += quantity;
    return true;
}

bool map_add_player(map_t *map, player_t *player)
{
    vector2u_t *position = player ? &player->position : NULL;

    if (!map || !player || MAP_OUT_POSITION(map, *position))
        return false;
    player->direction = PLAYER_RANDOM_DIRECTION();
    return list_push(
        map->cells[position->y][position->x].players,
        NODE_DATA_FROM_PTR(player)
    );
}

bool map_add_egg(map_t *map, egg_t *egg, vector2u_t *position)
{
    if (!map || !egg)
        return false;
    if (!list_push(map->cells[position->y][position->x].eggs,
        NODE_DATA_FROM_PTR(egg)
    )) {
        return false;
    }
    egg->position = *position;
    return true;
}
