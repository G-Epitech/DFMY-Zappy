/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** victory.c
*/

#include <string.h>
#include "utils.h"
#include "types/trantor/world.h"
#include "types/server.h"

static bool team_has_won(team_t *team)
{
    size_t winner_count = 0;
    node_t *node = team->players->first;
    player_t *player = NULL;

    if (team->players->len < 6)
        return false;
    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        if (player->level == 8)
            winner_count++;
        if (winner_count >= 6)
            return true;
        node = node->next;
    }
    return false;
}

bool app_handle_world_routine_team_victory(world_t *world, server_t *server)
{
    node_t *node = world->teams->first;
    team_t *team = NULL;

    while (node) {
        team = NODE_TO_PTR(node, team_t *);
        if (team_has_won(team)) {
            controllers_add_emission(server->controllers, CTRL_GRAPHIC,
                "seg %s\n", team->name
            );
            return true;
        }
        node = node->next;
    }
    return false;
}
