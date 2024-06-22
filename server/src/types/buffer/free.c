/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** free.c
*/

#include <stdlib.h>
#include "types/buffer.h"

void buffer_free(buffer_t *buffer)
{
    if (buffer)
        free(buffer->data);
    free(buffer);
}
