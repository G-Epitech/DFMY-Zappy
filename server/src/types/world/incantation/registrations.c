/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/incantation.h"

bool incantation_add_player(incantation_t *incantation, player_t *player)
{
    return list_push(incantation->players, NODE_DATA_FROM_PTR(player));
}

void incantation_remove_player(incantation_t *incantation, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    node_t *node = list_find(incantation->players, data);

    if (node)
        list_erase(incantation->players, node, NULL);
    if (player == incantation->requester)
        incantation->requester = NULL;
}
