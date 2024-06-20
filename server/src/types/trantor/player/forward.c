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
    vector2l_t pos = VECTOR2L_FROM_U(player->position);

    switch (player->direction) {
        case DIR_NORTH:
            pos.y -= 1;
            break;
        case DIR_EAST:
            pos.x += 1;
            break;
        case DIR_SOUTH:
            pos.y += 1;
            break;
        default:
            pos.x -= 1;
            break;
    }
    player->position = map_resolve_position(map, pos);
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
    cell = MAP_PLAYER_CELL(map, player);
    list_append(cell->players, node);
}
