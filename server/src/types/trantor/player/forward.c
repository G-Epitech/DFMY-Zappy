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
    node_t *node = NULL;
    map_cell_t *cell;

    if (!map || !player)
        return;
    cell = &(map->cells[player->position.y][player->position.x]);
    node = list_find(cell->players, NODE_DATA_FROM_PTR(player));
    if (!node)
        return;
    list_pop(cell->players, node);
    map_forward_position(map, &player->position, player->direction);
    cell = MAP_PLAYER_CELL(map, player);
    list_append(cell->players, node);
}
