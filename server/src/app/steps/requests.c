/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** requests.c
*/

#include "app.h"

static void app_handle_controller_invalid_request(controller_t *controller,
    request_t *request)
{
    if (controller_add_emission(controller, "ko\n"))
        request->status = REQ_FINISHED;
}

static void app_handle_controller_valid_request(app_t *app,
    controller_t *controller, request_t *request)
{
    switch (controller->generic.type) {
        case CTRL_PLAYER:
            app_handle_player_request(app, controller, request);
            break;
        case CTRL_GRAPHIC:
            app_handle_graphic_request(app, controller, request);
            break;
        default:
            app_handle_unknown_request(app, controller, request);
            break;
    }
}

bool app_handle_controller_request(app_t *app, controller_t *controller,
    request_t *request)
{
    switch (request->status) {
        case REQ_INVALID:
            app_handle_controller_invalid_request(controller, request);
            break;
        case REQ_READY:
        case REQ_HANDLING:
            app_handle_controller_valid_request(app, controller, request);
            break;
        default:
            break;
    }
    return request->status == REQ_FINISHED;
}

void app_handle_controller_requests(app_t *app, controller_t *controller)
{
    node_t *node = controller->generic.requests->first;
    node_t *next = NULL;
    request_t *request = NULL;
    bool complete = true;

    while (node && complete) {
        next = node->next;
        request = NODE_TO_PTR(node, request_t *);
        complete = app_handle_controller_request(app, controller, request);
        controller_clear_first_request(controller);
        node = next;
    }
}

void app_handle_controllers_requests(app_t *app)
{
    node_t *node = app->server->controllers->first;
    controller_t *controller = NULL;

    while (node) {
        controller = NODE_TO_PTR(node, controller_t *);
        if (CTRL_CAN_REQ(controller))
            app_handle_controller_requests(app, controller);
        node = node->next;
    }
}
