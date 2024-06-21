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

ssize_t buffer_vwritef(buffer_t *buffer, const char *format, va_list args)
{
    va_list copy;
    size_t available = buffer ? buffer->size - buffer->bytes : 0;
    ssize_t needed;
    ssize_t written;

    va_copy(copy, args);
    needed = vsnprintf(NULL, 0, format, args);
    va_end(copy);
    printf("needed: %ld, available: %ld\n", needed, available);
    if (!buffer || needed < 0 || needed > available)
        return -1;
    va_copy(copy, args);
    written = vsnprintf(&buffer->data[buffer->bytes],available, format, args);
    va_end(copy);
    if (written < 0)
        return -1;
    written = written == available ? written - 1 : written;
    buffer->bytes += written;
    return written;
}

ssize_t buffer_writef(buffer_t *buffer, const char *format, ...)
{
    va_list args;
    ssize_t written;

    if (!buffer)
        return 0;
    va_start(args, format);
    written = buffer_vwritef(buffer, format, args);
    va_end(args);
    return written;
}
