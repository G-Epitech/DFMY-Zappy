/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** victory.c
*/

#include <string.h>
#include "types/trantor/world.h"
#include "types/server.h"
#include "log.h"

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

static void notify_graphics(world_t *world, server_t *server)
{
    timeval_t game_duration = { 0 };

    world_get_game_duration(world, &game_duration);
    controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "seg %s\nsmg Game ended in %lds and %ldus\n",
        world->winner->name, game_duration.tv_sec, game_duration.tv_usec
    );
    log_info("Game ended in %lds and %ldus", game_duration.tv_sec,
        game_duration.tv_usec
    );
}

static void on_team_victory(world_t *world, server_t *server)
{
    node_t *node = server->controllers->first;
    controller_t *controller = NULL;

    world_end_game(world);
    notify_graphics(world, server);
    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        if (controller->generic.type == CTRL_PLAYER &&
            CTRL_CAN_REQ(controller)
        ) {
            controller->generic.state = CTRL_ALLOW_EMIT;
        }
        node = node->next;
    }
}

bool app_handle_world_routine_team_victory(world_t *world, server_t *server)
{
    node_t *node = world->teams->first;
    team_t *team = NULL;

    if (world->winner)
        return true;
    while (node && !world->winner) {
        team = NODE_TO_PTR(node, team_t *);
        if (team_has_won(team))
            world->winner = team;
        node = node->next;
    }
    if (world->winner)
        on_team_victory(world, server);
    return world->winner != NULL;
}
