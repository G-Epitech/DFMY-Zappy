/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include <string.h>
#include "app.h"

static bool parse_player_id(incoming_token_t *token, size_t *id)
{
    char str_token[32] = { 0 };
    char *end_ptr = NULL;

    if (token->size >= 32)
        return false;
    memcpy(str_token, token->content, token->size);
    *id = strtoul(str_token, &end_ptr, 10);
    return end_ptr != &str_token[0];
}

static bool find_player_by_id(app_t *app, size_t id, player_t **player)
{
    node_t *node = app->world->players->first;
    player_t *current = NULL;

    while (node) {
        current = NODE_TO_PTR(node, player_t *);
        if (current->id == id) {
            *player = current;
            return true;
        }
        node = node->next;
    }
    return false;
}

static bool handle_arguments(controller_t *controller, request_t *request,
    const char *command, size_t *id)
{
    incoming_token_t token = { 0 };

    if (request_get_token(request, 2, &token)) {
        controller_add_emission(controller, "sbp\n");
        log_warn("Too many arguments for '%s' command", command);
        return false;
    }
    if (!request_get_token(request, 1, &token)) {
        controller_add_emission(controller, "sbp\n");
        log_warn("Not enough arguments for '%s' command", command);
        return false;
    }
    if (!parse_player_id(&token, id)) {
        controller_add_emission(controller, "sbp\n");
        log_warn("Invalid player id for for '%s' command", command);
        return false;
    }
    return true;
}

void app_handle_gui_request_player_position(app_t *app,
    controller_t *controller, request_t *request)
{
    player_t *player = NULL;
    size_t id = 0;

    if (!handle_arguments(controller, request, "ppo", &id))
        return;
    if (!find_player_by_id(app, id, &player)) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("Player with id %zu not found", id);
    }
    controller_add_emission(controller, "ppo %zu %zu %zu %u\n",
        player->id, player->position.x, player->position.y, player->direction
    );
}

void app_handle_gui_request_player_level(app_t *app,
    controller_t *controller, request_t *request)
{
    player_t *player = NULL;
    size_t id = 0;

    if (!handle_arguments(controller, request, "plv", &id))
        return;
    if (!find_player_by_id(app, id, &player)) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("Player with id %zu not found", id);
    }
    controller_add_emission(controller, "plv %zu %zu\n",
        player->id, player->level
    );
}

void app_handle_gui_request_player_inventory(app_t *app,
    controller_t *controller, request_t *request)
{
    player_t *player = NULL;
    size_t id = 0;

    if (!handle_arguments(controller, request, "pin", &id))
        return;
    if (!find_player_by_id(app, id, &player)) {
        controller_add_emission(controller, "sbp\n");
        return log_warn("Player with id %zu not found", id);
    }
    controller_add_emission(controller,
        "pin %zu %zu %zu %zu %zu %zu %zu %zu %zu %zu\n",
        player->id, player->position.x, player->position.y,
        player->inventory[RES_FOOD], player->inventory[RES_LINEMATE],
        player->inventory[RES_DERAUMERE], player->inventory[RES_SIBUR],
        player->inventory[RES_MENDIANE], player->inventory[RES_PHIRAS],
        player->inventory[RES_THYSTAME]
    );
}
