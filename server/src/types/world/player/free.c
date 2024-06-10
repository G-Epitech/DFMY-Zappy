/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Player new
*/

#include "types/world/player.h"

void player_free(player_t *player)
{
    if (player)
        free(player);
}

void player_free_as_node_data(void *data)
{
    player_free((player_t *)data);
}
