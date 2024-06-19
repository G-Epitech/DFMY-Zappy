/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#include "types/trantor/player.h"
#include "types/trantor/map.h"

static void increment_player_position(map_t *map, player_t *player)
{
    switch (player->direction) {
        case DIR_NORTH:
            player->position.y = (player->position.y + 1) % map->size.y;
            break;
        case DIR_EAST:
            player->position.x = (player->position.x + 1) % map->size.x;
            break;
        case DIR_SOUTH:
            player->position.y = (player->position.y - 1) % map->size.y;
            break;
        default:
            player->position.x = (player->position.x - 1) % map->size.x;
            break;
    }
}

void player_forward(map_t *map, player_t *player)
{
    node_t *node = NULL;
    map_cell_t *cell;

    if (!map || !player)
        return;
    cell = &(map->cells[player->position.y][player->position.x]);
    node = list_find(cell->players, NODE_DATA_FROM_PTR(player));
    if (!node)
        return;
    list_pop(cell->players, node);
    increment_player_position(map, player);
    cell = &(map->cells[player->position.y][player->position.x]);
    list_append(cell->players, node);
}
