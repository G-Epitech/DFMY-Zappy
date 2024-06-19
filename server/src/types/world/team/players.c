/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** add.c
*/

#include "types/world/team.h"
#include "types/world/player.h"

bool team_add_player(team_t *team, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);

    if (!list_push(team->players, data))
        return false;
    player->team = team;
    return true;
}

void team_remove_player(team_t *team, player_t *player)
{
    node_data_t data = NODE_DATA_FROM_PTR(player);
    node_t *node = team ? list_find(team->players, data) : NULL;

    if (node)
        list_erase(team->players, node, NULL);
    player->team = NULL;
}
