/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/trantor/player.h"
#include "types/trantor/incantation.h"

bool incantation_add_player(incantation_t *incantation, player_t *player)
{
    if (!player)
        return false;
    if (player->incantation)
        return true;
    if (!list_push(incantation->players, NODE_DATA_FROM_PTR(player)))
        return false;
    player->incantation = incantation;
    return true;
}

bool incantation_add_players_from_cell(incantation_t *incantation,
    map_cell_t *cell)
{
    node_t *node = cell->players->first;
    player_t *player = NULL;

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        if (player->level != (incantation->level - 1)) {
            node = node->next;
            continue;
        }
        if (!incantation_add_player(incantation, player))
            return false;
        node = node->next;
    }
    return true;
}

void incantation_remove_player(incantation_t *incantation, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    node_t *node = list_find(incantation->players, data);

    if (node)
        list_erase(incantation->players, node, NULL);
    if (player == incantation->requester)
        incantation->requester = NULL;
    if (player->incantation == incantation)
        player->incantation = NULL;
}

void incantation_remove_all_players(incantation_t *incantation)
{
    node_t *node = incantation->players->first;
    node_t *next = NULL;
    player_t *player = NULL;

    while (node) {
        next = node->next;
        player = NODE_TO_PTR(node, player_t *);
        player->incantation = NULL;
        list_erase(incantation->players, node, NULL);
        node = next;
    }
}
