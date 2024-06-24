/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "app.h"

void app_handle_gui_request_teams_names(app_t *app, controller_t *controller,
    request_t *request)
{
    node_t *node = app->world->teams->first;
    request_token_t token = { 0 };
    team_t *team = NULL;

    if (request_get_token(request, 1, &token)) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("No arguments expected for 'tna' command");
    }
    while (node) {
        team = NODE_TO_PTR(node, team_t *);
        controller_add_emission(controller, "tna %s\n", team->name);
        node = node->next;
    }
}
