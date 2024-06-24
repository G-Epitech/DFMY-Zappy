/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** move.c
*/

#include <stdio.h>
#include "types/trantor/map.h"
#include "types/trantor/player.h"

void map_move_player_node(map_t *map, node_t *player_node, vector2u_t *new_pos)
{
    player_t *player = NODE_TO_PTR(player_node, player_t *);
    map_cell_t *old_cell = MAP_PLAYER_CELL(map, player);
    map_cell_t *new_cell = MAP_CELL_AT_POS(map, *new_pos);

    list_pop(old_cell->players, player_node);
    list_append(new_cell->players, player_node);
    player->position = *new_pos;
}

void map_move_player(map_t *map, player_t *player, vector2u_t *new_pos)
{
    node_t *player_node = NULL;
    map_cell_t *player_cell = MAP_PLAYER_CELL(map, player);

    player_node = list_find(player_cell->players, NODE_DATA_FROM_PTR(player));
    if (player_node)
        return map_move_player_node(map, player_node, new_pos);
}
