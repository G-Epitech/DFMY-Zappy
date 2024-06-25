/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** forward.c
*/

#include "app.h"

bool app_handle_player_request_inventory_onstart(
    __attribute_maybe_unused__ app_t *app,
    __attribute_maybe_unused__ player_controller_t *controller,
    request_t *request)
{
    request_token_t token = { 0 };

    if (request_get_token(request, 1, &token)) {
        log_warn("No arguments expected for 'Inventory' command");
        return false;
    }
    return true;
}

void app_handle_player_request_inventory_onfinish(
    __attribute_maybe_unused__ app_t *app,
    player_controller_t *controller,
    __attribute_maybe_unused__ request_t *request)
{
    player_t *player = controller->player;

    controller_add_emission((controller_t *) controller,
        "[food %zu, linemate %zu, deraumere %zu, sibur %zu, mendiane %zu, "
        "phiras %zu, thystame %zu]\n",
        player->inventory[RES_FOOD], player->inventory[RES_LINEMATE],
        player->inventory[RES_DERAUMERE], player->inventory[RES_SIBUR],
        player->inventory[RES_MENDIANE], player->inventory[RES_PHIRAS],
        player->inventory[RES_THYSTAME]
    );
}
