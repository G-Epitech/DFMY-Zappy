/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** unsubscribe.c
*/

#include "types/list.h"
#include "types/controller.h"
#include "types/shared_event.h"

bool shared_event_unsubscribe(shared_event_t *event, controller_t *controller)
{
    node_t *node = NULL;
    controller_t *sub = NULL;

    if (!event || !controller)
        return false;
    node = event->subscribers->first;
    while (node) {
        sub = NODE_DATA_TO_PTR(node->data, controller_t *);
        if (sub == controller) {
            list_pop(event->subscribers, node);
            return true;
        }
    }
    return false;
}
