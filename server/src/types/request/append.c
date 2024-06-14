/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** append.c
*/

#include <memory.h>
#include "types/request.h"

bool request_append(request_t *request, const char *data, size_t size)
{
    char *new_buffer = NULL;

    size = size > REQUEST_BUFF_SIZE ? REQUEST_BUFF_SIZE : size;
    if (request->content_size + size > request->buffer_size) {
        request->buffer_size += REQUEST_BUFF_SIZE;
        new_buffer = realloc(request->buffer, request->buffer_size + 1);
        if (!new_buffer)
            return false;
        memset(new_buffer + request->content_size, 0, REQUEST_BUFF_SIZE + 1);
        request->buffer = new_buffer;
    }
    memcpy(request->buffer + request->content_size, data, size);
    request->content_size += size;
    return true;
}
