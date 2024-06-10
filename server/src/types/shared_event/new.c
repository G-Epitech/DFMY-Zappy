/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <stdlib.h>
#include "types/shared_event.h"

shared_event_t *shared_event_new(char *buffer, size_t buffer_size)
{
    shared_event_t *event = calloc(1, sizeof(shared_event_t));

    if (!event) {
        free(buffer);
        return NULL;
    }
    event->buffer = buffer;
    event->buffer_size = buffer_size;
    event->subscribers = list_new();
    if (!event->subscribers) {
        shared_event_free(event);
        return NULL;
    }
    return event;
}
