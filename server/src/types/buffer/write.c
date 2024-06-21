/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "types/buffer.h"

size_t buffer_write(buffer_t *buffer, const char *data, size_t size)
{
    if (!buffer || !data || !size)
        return 0;
    if (buffer->bytes + size > buffer->size)
        size = buffer->size - buffer->bytes;
    if (!size)
        return 0;
    memcpy(&buffer->data[buffer->bytes], data, size);
    buffer->bytes += size;
    return size;
}

ssize_t buffer_writef(buffer_t *buffer, const char *format, ...)
{
    va_list args;
    size_t size;
    ssize_t written;

    if (!buffer)
        return 0;
    size = buffer->size - buffer->bytes;
    va_start(args, format);
    written = vsnprintf(&buffer->data[buffer->bytes],size, format, args);
    va_end(args);
    if (written < 0)
        return -1;
    written = written == size ? written - 1 : written;
    buffer->bytes += written;
    return written;
}
