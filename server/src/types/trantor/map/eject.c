/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** move.c
*/

#include <stdio.h>
#include "types/trantor/map.h"
#include "types/trantor/player.h"

static void update_position_and_notify_players(list_t *players,
    vector2u_t new_pos, direction_t direction)
{
    node_t *node = NULL;
    player_t *player = NULL;
    direction_t incoming_direction = direction_reverse(direction);

    node = players->first;
    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        player->position = new_pos;
        controller_add_emission((controller_t *)player->controller,
            "eject %d\n", incoming_direction);
        node = node->next;
    }
}

bool map_eject_players(map_t *map, player_t *player)
{
    vector2u_t new_pos = player->position;
    map_cell_t *old_cell = NULL;
    map_cell_t *new_cell = NULL;
    node_t *node = NULL;

    map_forward_position(map, &new_pos, player->direction);
    old_cell = MAP_CELL_AT_POS(map, player->position);
    new_cell = MAP_CELL_AT_POS(map, new_pos);
    if (!old_cell->players || !new_cell->players)
        return false;
    node = list_find(old_cell->players, NODE_DATA_FROM_PTR(player));
    if (!node)
        return false;
    list_pop(old_cell->players, node);
    update_position_and_notify_players(old_cell->players, new_pos,
        player->direction);
    list_merge(new_cell->players, old_cell->players);
    list_append(old_cell->players, node);
    return true;
}
