/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** events.c
*/

#include <unistd.h>
#include <string.h>
#include "log.h"
#include "types/emission.h"
#include "types/server.h"
#include "types/controller.h"

/*static void server_event_handle_propagate_fail(controller_t *controller,
    shared_event_t *event, ssize_t write_size)
{
    char *buffer = strndup(event->buffer - write_size + 1, write_size);
    size_t buffer_size = event->buffer_size - write_size;

    shared_event_unsubscribe(event, controller);
    if (!buffer)
        return;
    log_info("Failed to propagate event to %d... converting to emission",
        controller->generic.socket);
    controller_add_emission(controller, buffer, buffer_size);
}*/

static void server_event_handle_write(controller_t *controller,
    shared_event_t *event, fd_states_t actual)
{
    ssize_t write_size;

    if (FD_ISSET(controller->generic.socket, &actual.writable)) {
        write_size = controller_write(controller,
            event->buffer, event->buffer_size);
        if (write_size != event->buffer_size && write_size != 0) {
            /*server_event_handle_propagate_fail(controller, event, write_size);*/
        }
    }
}

void server_propagate_event(server_t *server, shared_event_t *event)
{
    list_t *subscribers = event->subscribers;
    node_t *node = subscribers->first;
    controller_t *controller = NULL;

    log_info("Propagating event [%s]", event->buffer);
    while (node) {
        controller = NODE_DATA_TO_PTR(node->data, controller_t *);
        server_event_handle_write(controller, event, server->fd_actual);
        node = node->next;
    }
}

void server_propagate_events(server_t *server)
{
    node_t *node = server->events->first;
    shared_event_t *event = NULL;

    while (node) {
        event = NODE_DATA_TO_PTR(node->data, shared_event_t *);
        server_propagate_event(server, event);
        list_erase(server->events, node, &shared_event_free_as_node_data);
        node = server->events->first;
    }
}
