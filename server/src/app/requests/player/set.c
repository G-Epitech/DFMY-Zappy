/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** forward.c
*/

#include <string.h>
#include "app.h"
#include "types/trantor/egg.h"

static bool is_valid_resource(request_token_t *token)
{
    char str_resource[RES_MAX_STRING_LEN + 1] = { 0 };
    resource_t resource;

    if (token->size > RES_MAX_STRING_LEN) {
        log_warn("Invalid resource name");
        return false;
    }
    memcpy(str_resource, token->content, token->size);
    if (!resource_from_string(&resource, str_resource)) {
        log_warn("Invalid resource name '%s'", str_resource);
        return false;
    }
    return true;
}

bool app_handle_player_request_set_onstart(
    __attribute_maybe_unused__ app_t *app,
    __attribute_maybe_unused__ player_controller_t *controller,
    request_t *request)
{
    request_token_t token = { 0 };

    if (request_get_token(request, 2, &token)) {
        log_warn("Too many arguments for 'Set' command");
        return false;
    }
    if (!request_get_token(request, 1, &token)) {
        log_warn("Not enough arguments for 'Set' command");
        return false;
    }
    return is_valid_resource(&token);
}

void app_handle_player_request_set_onfinish(app_t *app,
    player_controller_t *controller,
    __attribute_maybe_unused__ request_t *request)
{
    char str_resource[RES_MAX_STRING_LEN + 1] = { 0 };
    request_token_t token = { 0 };
    resource_t resource;

    if (!request_get_token(request, 1, &token)) {
        controller_add_emission((controller_t *) controller, "ko\n");
        return;
    }
    memcpy(str_resource, token.content, token.size);
    resource_from_string(&resource, str_resource);
    if (!player_set_object(controller->player, app->world->map, resource)) {
        controller_add_emission((controller_t *) controller, "ko\n");
        return;
    }
    controller_add_emission((controller_t *) controller, "ok\n");
    controllers_add_emission(app->server->controllers, CTRL_GRAPHIC,
        "pdr %zu %d\n", controller->player->id, resource);
    // TODO: remove useless step
    controllers_add_emission(app->server->controllers, CTRL_GRAPHIC,
        "pin %zu %zu %zu %zu %zu %zu %zu %zu %zu %zu\n",
        controller->player->id, controller->player->position.x, controller->player->position.y,
        controller->player->inventory[RES_FOOD], controller->player->inventory[RES_LINEMATE],
        controller->player->inventory[RES_DERAUMERE], controller->player->inventory[RES_SIBUR],
        controller->player->inventory[RES_MENDIANE], controller->player->inventory[RES_PHIRAS],
        controller->player->inventory[RES_THYSTAME]
    );
}
