/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** forward.c
*/

#include "app.h"
#include "types/trantor/egg.h"

static void emit_message_to_player(world_t *world, player_t *emitter,
    player_t *player, incoming_token_t *token)
{
    controller_t *controller = (controller_t *) player->controller;
    double angle = map_get_sound_angle(world->map, emitter->position,
        player->position);
    int quadrant = angle_to_quadrant(angle);
    int normalized_quadrant = direction_get_quadrant(player->direction,
        quadrant);

    if (emitter->position.x == player->position.x &&
        emitter->position.y == player->position.y
    ) {
        normalized_quadrant = 0;
    }
    controller_add_emission(controller, "message %d, ", normalized_quadrant);
    controller_add_emission_raw(controller, token->content, token->size);
    controller_add_emission_raw(controller, "\n", 1);
    log_warn("T%zu send message to T%zu with quadrant %d", emitter->id, player->id, normalized_quadrant);
}

static void emit_message_to_players(world_t *world, player_t *emitter,
    incoming_token_t *token)
{
    node_t *node = world->players->first;
    player_t *player = NULL;

    while (node) {
        player = NODE_TO_PTR(node, player_t *);
        if (player != emitter)
            emit_message_to_player(world, emitter, player, token);
        node = node->next;
    }
}

static void notify_graphics(server_t *server, player_t *player,
    incoming_token_t *token)
{
    controllers_add_emission(server->controllers, CTRL_GRAPHIC,
        "pbc %zu ", player->id);
    controllers_add_emission_raw(server->controllers, CTRL_GRAPHIC,
        token->content, token->size);
    controllers_add_emission_raw(server->controllers, CTRL_GRAPHIC, "\n", 1);
}

bool app_handle_player_request_broadcast_onstart(
    __attribute_maybe_unused__ app_t *app,
    __attribute_maybe_unused__ player_controller_t *controller,
    request_t *request)
{
    incoming_token_t token = { 0 };

    if (!request_get_token(request, 1, &token)) {
        log_warn("Not enough arguments for 'Broadcast' command");
        return false;
    }
    return true;
}

void app_handle_player_request_broadcast_onfinish(app_t *app,
    player_controller_t *controller,
    __attribute_maybe_unused__ request_t *request)
{
    incoming_token_t token = { 0 };

    if (!request_get_token(request, 1, &token) ||
        (request->content_size - STR_STRICT_SIZEOF("Broadcast ") <= 0)
    ) {
        controller_add_emission((controller_t *) controller, "ko\n");
        return;
    }
    token.size = request->content_size - STR_STRICT_SIZEOF("Broadcast ");
    emit_message_to_players(app->world, controller->player, &token);
    notify_graphics(app->server, controller->player, &token);
    controller_add_emission((controller_t *) controller, "ok\n");
}
