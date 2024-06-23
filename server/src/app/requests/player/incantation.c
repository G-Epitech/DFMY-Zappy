/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** forward.c
*/

#include <string.h>
#include "app.h"
#include "types/trantor/egg.h"

static void notify_incantation_start(server_t *server,
    incantation_t *incantation)
{
    node_t *node = incantation->players->first;
    player_t *player = NULL;

    controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "pic %zu %zu %u %zu", incantation->location.x,
        incantation->location.y, incantation->level,
        incantation->requester->id);
    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        if (player != incantation->requester) {
            controller_add_emission((controller_t *) player->controller,
                "Elevation underway\n");
            controllers_add_emission(server->controllers, CTRL_GRAPHIC,
                " %zu%c", player->id, node->next ? ' ' : '\n');
        }
        node = node->next;
    }
}

bool app_handle_player_request_incantation_onstart(app_t *app,
    player_controller_t *controller, request_t *request)
{
    request_token_t token = { 0 };
    incantation_t *incantation = NULL;

    if (request_get_token(request, 1, &token)) {
        log_warn("No arguments expected for 'Incantation' command");
        return false;
    }
    incantation = world_start_incantation(app->world, controller->player);
    if (!incantation) {
        controller_add_emission((controller_t *) controller, "ko\n");
        return false;
    }
    notify_incantation_start(app->server, incantation);
    return true;
}
