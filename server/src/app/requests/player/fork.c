/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** forward.c
*/

#include "app.h"
#include "types/trantor/egg.h"

bool app_handle_player_request_fork_onstart(
    __attribute_maybe_unused__ app_t *app,
    player_controller_t *controller,
    request_t *request)
{
    incoming_token_t token = { 0 };
    player_t *player = controller->player;

    if (request_get_token(request, 1, &token)) {
        log_warn("No arguments expected for 'Fork' command");
        return false;
    }
    controllers_add_emission(app->server->controllers, CTRL_GRAPHIC,
        "pfk %zu\n", player->id);
    return true;
}

void app_handle_player_request_fork_onfinish(app_t *app,
    player_controller_t *controller,
    __attribute_maybe_unused__ request_t *request)
{
    team_t *team = controller->player->team;
    player_t *player = controller->player;
    egg_t *egg = world_add_egg(app->world, team, player);

    if (egg) {
        controller_add_emission((controller_t *) controller, "ok\n");
        controllers_add_emission(app->server->controllers, CTRL_GRAPHIC,
            "enw %zu %zu %zu %zu\n", egg->id, egg->laid_by, egg->position.x,
            egg->position.y
        );
    } else {
        controller_add_emission((controller_t *) controller, "ko\n");
        log_error("Failed to add new egg in team %s", team->name);
    }
}
