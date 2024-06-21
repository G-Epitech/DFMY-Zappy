/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Player
*/

#include "types/trantor/player.h"
#include "types/trantor/map.h"

void player_forward(player_t *player, map_t *map)
{
    node_t *node;
    map_cell_t *cell;

    if (!map || !player)
        return;
    cell = MAP_PLAYER_CELL(map, player);
    node = map_cell_pop_player(cell, player);
    if (!node)
        return;
    map_forward_position(map, &player->position, player->direction);
    cell = MAP_PLAYER_CELL(map, player);
    list_append(cell->players, node);
}
