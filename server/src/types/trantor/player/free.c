/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Player new
*/

#include "types/trantor/player.h"

void player_free(player_t *player)
{
    free(player);
}

void player_free_as_node_data(node_data_t data)
{
    player_free(NODE_DATA_TO_PTR(data, player_t *));
}
