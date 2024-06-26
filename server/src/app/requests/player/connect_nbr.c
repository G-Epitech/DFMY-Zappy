/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** forward.c
*/

#include "app.h"

bool app_handle_player_request_connect_nbr_onstart(
    __attribute_maybe_unused__ app_t *app,
    __attribute_maybe_unused__ player_controller_t *controller,
    request_t *request)
{
    incoming_token_t token = { 0 };

    if (request_get_token(request, 1, &token)) {
        log_warn("No arguments expected for 'Connect_nbr' command");
        return false;
    }
    return true;
}

void app_handle_player_request_connect_nbr_onfinish(
    __attribute_maybe_unused__ app_t *app,
    player_controller_t *controller,
    __attribute_maybe_unused__ request_t *request)
{
    team_t *team = controller->player->team;
    size_t available = 0;

    if (team)
        available = team->eggs->len;
    controller_add_emission((controller_t *) controller, "%zu\n",
        available);
}
