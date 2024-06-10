/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** free.c
*/

#include <stdlib.h>
#include "types/shared_event.h"

void shared_event_free(shared_event_t *event)
{
    if (!event)
        return;
    free(event->buffer);
    list_free(event->subscribers, NULL);
    free(event);
}
