/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** victory.c
*/

#include <string.h>
#include "utils.h"
#include "types/world/world.h"
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

static void send_victory_msg(list_t *all_ctrls, char *winning_team_name)
{
    emission_params_t params = {0};

    if (my_asprintf(&params.buffer, "seg %s", winning_team_name) == -1)
        return;
    params.buffer_size = strlen(params.buffer);
    params.flags = EMISSION_COMPLETE;
    controllers_add_emission(all_ctrls, &params, CTRL_GRAPHIC);
}

bool app_handle_world_routine_team_victory(world_t *world, server_t *server)
{
    node_t *node = world->teams->first;
    team_t *team = NULL;

    while (node) {
        team = NODE_TO_PTR(node, team_t *);
        if (team_has_won(team)) {
            send_victory_msg(server->controllers, team->name);
            return true;
        }
        node = node->next;
    }
    return false;
}
