/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <stdlib.h>
#include "types/buffer.h"

ssize_t buffer_read_from(buffer_t *buffer, int fd)
{
    char *read_head = buffer->data + buffer->bytes;
    size_t available = buffer->size - buffer->bytes;
    ssize_t read_bytes = read(fd, read_head, available);

    if (read_bytes <= 0)
        return read_bytes;
    buffer->bytes += read_bytes;
    return read_bytes;
}
