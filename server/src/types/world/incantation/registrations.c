/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/player.h"
#include "types/world/incantation.h"

bool incantation_add_player(incantation_t *incantation, player_t *player)
{
    if (!player || player->incantation)
        return false;
    if (!list_push(incantation->players, NODE_DATA_FROM_PTR(player)))
        return false;
    player->incantation = incantation;
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
    player_t *player = NULL;

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        incantation_remove_player(incantation, player);
        node = node->next;
    }
}
