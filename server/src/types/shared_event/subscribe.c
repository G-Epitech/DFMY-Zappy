/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** register.c
*/

#include "types/controller.h"
#include "types/shared_event.h"

bool shared_event_subscribe(shared_event_t *event, controller_t *controller)
{
    if (!event || !controller)
        return false;
    return list_push(event->subscribers, NODE_DATA_FROM_PTR(controller));
}

void shared_event_subscribe_graphics(shared_event_t *event,
    list_t *controllers)
{
    node_t *node = controllers->first;
    controller_t *controller = NULL;

    while (node) {
        controller = NODE_DATA_TO_PTR(node->data, controller_t *);
        if (controller->generic.type == CTRL_GRAPHIC) {
            shared_event_subscribe(event, controller);
        }
        node = node->next;
    }
}

void shared_event_subscribe_players(shared_event_t *event, list_t *controllers)
{
    node_t *node = controllers->first;
    controller_t *controller = NULL;

    while (node) {
        controller = NODE_DATA_TO_PTR(node->data, controller_t *);
        if (controller->generic.type == CTRL_PLAYER) {
            shared_event_subscribe(event, controller);
        }
        node = node->next;
    }
}

void shared_event_subscribe_all(shared_event_t *event, list_t *controllers)
{
    node_t *node = controllers->first;
    controller_t *controller = NULL;

    while (node) {
        controller = NODE_DATA_TO_PTR(node->data, controller_t *);
        shared_event_subscribe(event, controller);
        node = node->next;
    }
}
