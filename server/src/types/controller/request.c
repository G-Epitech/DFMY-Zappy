/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** player.c
*/

#include "types/controller.h"
#include "log.h"

static request_t *generic_controller_create_request(
    generic_controller_t *generic)
{
    request_t *req = request_new();

    if (!req) {
        log_error("Failed to create request. Ignored.");
        return NULL;
    }
    if (!list_push(generic->requests, NODE_DATA_FROM_PTR(req))) {
        log_error("Failed to append request in queue. Ignored.");
        request_free(req);
        return NULL;
    }
    return req;
}

static request_t *player_controller_create_request(
    player_controller_t *controller)
{
    if (controller->requests->len == CTRL_PLAYER_MAX_REQ) {
        log_info("Player controller %d reached max allowed pending requests. "
            "Ignored.", controller->socket);
        return NULL;
    }
    return generic_controller_create_request(
        (generic_controller_t *) controller
    );
}

static request_t *graphic_controller_create_request(
    graphic_controller_t *controller)
{
    return generic_controller_create_request(
        (generic_controller_t *) controller
    );
}

request_t *controller_get_last_request(controller_t *controller)
{
    if (controller->generic.requests->last)
        return NODE_TO_PTR(controller->generic.requests->last, request_t *);
    return NULL;
}

request_t *controller_get_next_pending_request(controller_t *controller)
{
    request_t *req = controller_get_last_request(controller);

    if (req && req->status == REQ_PENDING)
        return req;
    switch (controller->generic.type) {
        case CTRL_PLAYER:
            return player_controller_create_request(&controller->player);
        case CTRL_GRAPHIC:
            return graphic_controller_create_request(&controller->graphic);
        default:
            return generic_controller_create_request(&controller->generic);
    }
}
