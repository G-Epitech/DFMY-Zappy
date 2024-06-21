/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <string.h>
#include <stdlib.h>
#include "types/buffer.h"

buffer_t *buffer_resize(buffer_t *buffer, size_t new_size)
{
    char *new_data;

    if (!buffer || !new_size)
        return NULL;
    new_data = realloc(buffer->data, new_size);
    if (!new_data) {
        buffer_free(buffer);
        return NULL;
    }
    buffer->data = new_data;
    buffer->size = new_size;
    return buffer;
}
