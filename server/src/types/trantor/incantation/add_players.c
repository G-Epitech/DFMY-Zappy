/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** add_players.c
*/

#include "types/trantor/incantation.h"
#include "types/trantor/player.h"

void incantation_add_players_from_cell(incantation_t *incantation,
    map_cell_t *cell)
{
    node_t *node = cell->players->first;
    player_t *player = NULL;

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        if (player->level == (incantation->level - 1)) {
            incantation_add_player(incantation, player);
        }
        node = node->next;
    }
}
