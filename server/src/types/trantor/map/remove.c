/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/trantor/map.h"
#include "types/trantor/egg.h"
#include "types/trantor/player.h"

void map_remove_resource(map_t *map, vector2u_t pos, resource_t resource,
    size_t quantity)
{
    if (!map || map->cells[pos.y][pos.x].resources[resource] == 0)
        return;
    map->cells[pos.y][pos.x].resources[resource] -= quantity;
}

void map_remove_player(map_t *map, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    map_cell_t *cell = NULL;
    node_t *node = NULL;

    if (MAP_OUT_POSITION(map, player->position))
        return;
    cell = MAP_PLAYER_CELL(map, player);
    node = list_find(cell->players, data);
    if (node)
        list_erase(cell->players, node, NULL);
}

void map_remove_egg(map_t *map, egg_t *egg)
{
    node_data_t data = NODE_DATA_FROM_PTR(egg);
    map_cell_t *cell = NULL;
    node_t *node = NULL;

    if (MAP_OUT_POSITION(map, egg->position))
        return;
    cell = MAP_EGG_CELL(map, egg);
    node = list_find(cell->eggs, data);
    if (node)
        list_erase(cell->eggs, node, NULL);
}
