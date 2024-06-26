/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <stdlib.h>
#include <string.h>
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

size_t buffer_read(buffer_t *buffer, size_t size)
{
    return size > buffer->bytes ? buffer->bytes : size;
}

size_t buffer_read_delim(buffer_t *buffer, int delim)
{
    char *start = buffer->data;
    char *end = memchr(start, delim, buffer->size);

    if (end) {
        return (end - start + 1);
    } else {
        return buffer->bytes;
    }
}
