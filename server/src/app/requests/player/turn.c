/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** forward.c
*/

#include "app.h"

static void notify_graphics(server_t *server, player_t *player)
{
    controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "ppo %zu %zu %zu %u\n",
        player->id, player->position.x, player->position.y, player->direction
    );
}

bool app_handle_player_request_turn_right_onstart(
    __attribute_maybe_unused__ app_t *app,
    __attribute_maybe_unused__ player_controller_t *controller,
    request_t *request)
{
    request_token_t token = { 0 };

    if (request_get_token(request, 1, &token)) {
        log_warn("No arguments expected for 'Right' command");
        return false;
    }
    return true;
}


bool app_handle_player_request_turn_left_onstart(
    __attribute_maybe_unused__ app_t *app,
    __attribute_maybe_unused__ player_controller_t *controller,
    request_t *request)
{
    request_token_t token = { 0 };

    if (request_get_token(request, 1, &token)) {
        log_warn("No arguments expected for 'Left' command");
        return false;
    }
    return true;
}

void app_handle_player_request_turn_right_onfinish(app_t *app,
    player_controller_t *controller,
    __attribute_maybe_unused__ request_t *request)
{
    player_t *player = controller->player;

    player_change_direction(player, PLAYER_DIRECTION_RIGHT_OFFSET);
    notify_graphics(app->server, player);
    controller_add_emission((controller_t *) controller, "ok\n");
}

void app_handle_player_request_turn_left_onfinish(app_t *app,
    player_controller_t *controller,
    __attribute_maybe_unused__ request_t *request)
{
    player_t *player = controller->player;

    player_change_direction(player, PLAYER_DIRECTION_LEFT_OFFSET);
    notify_graphics(app->server, player);
    controller_add_emission((controller_t *) controller, "ok\n");
}
