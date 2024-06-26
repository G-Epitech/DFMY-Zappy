/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <string.h>
#include <stdio.h>
#include "types/buffer.h"

ssize_t buffer_flush(buffer_t *buffer, int fd)
{
    ssize_t written;

    if (!buffer || !buffer->bytes)
        return 0;
    written = write(fd, buffer->data, buffer->bytes);
    if (written < 0)
        return -1;
    if (written < buffer->bytes) {
        memmove(buffer->data, &buffer->data[written],
            buffer->bytes - written
        );
    }
    buffer->bytes -= written;
    return written;
}

void buffer_clear(buffer_t *buffer)
{
    if (!buffer)
        return;
    buffer->bytes = 0;
}

void buffer_clear_size(buffer_t *buffer, size_t size)
{
    if (!buffer || !size)
        return;
    if (size >= buffer->size) {
        buffer->bytes = 0;
        return;
    }
    memmove(buffer->data, &buffer->data[size], buffer->bytes - size);
    buffer->bytes -= size;
}
