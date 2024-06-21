/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <stdlib.h>
#include "types/buffer.h"

void buffer_init(buffer_t *buffer, size_t size)
{
    buffer->size = size;
    buffer->bytes = 0;
}

buffer_t *buffer_new(size_t size)
{
    buffer_t *buffer = calloc(1,sizeof(buffer_t));

    if (!buffer)
        return NULL;
    buffer->data = calloc(size, sizeof(char));
    if (!buffer->data) {
        free(buffer);
        return NULL;
    }
    buffer_init(buffer, size);
    return buffer;
}
