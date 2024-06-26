/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** requests.c
*/

#include "app.h"

void app_handle_controller_request(app_t *app, controller_t *controller,
    incoming_token_t *token)
{
    switch (controller->generic.type) {
        case CTRL_PLAYER:
            app_handle_player_request(app, controller, token);
            break;
        case CTRL_GRAPHIC:
            app_handle_graphic_request(app, controller, token);
            break;
        default:
            app_handle_unknown_request(app, controller, token);
            break;
    }
}

bool app_handle_controller_next_incoming_token(app_t *app,
    controller_t *controller)
{
    incoming_token_t token = { 0 };
    bool last = controller_read_next_incoming_token(controller, &token);

    if (token.size == 0)
        return false;
    // TODO: handle request
    if (token.consumed || controller_incoming_buffer_is_full(controller))
        controller_consume_incoming_token(controller, &token);
    return token.consumed ? !last : false;
}

void app_handle_controllers_incoming_tokens(app_t *app)
{
    node_t *node = app->server->controllers->first;
    controller_t *controller = NULL;
    bool has_next = false;

    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        if (CTRL_CAN_REQ(controller))
            has_next |= app_handle_controller_next_incoming_token(app, controller);
        node = node->next;
    }
}
