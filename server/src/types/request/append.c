/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** append.c
*/

#include <memory.h>
#include "types/request.h"
#include "log.h"

static bool request_resize(request_t *request)
{
    char *new_buffer = NULL;

    if (request->buffer_size >= REQ_MAX_BUFF_SIZE) {
        request->status = REQ_INVALID;
        log_error("Request buffer reached max size (%u bytes). "
            "Request marked as invalid.", REQ_MAX_BUFF_SIZE);
        return false;
    }
    request->buffer_size += REQ_BUFF_SIZE;
    new_buffer = realloc(request->buffer, request->buffer_size + 1);
    if (!new_buffer) {
        request->status = REQ_INVALID;
        log_error("Failed to resize request buffer. "
            "Request marked as invalid.");
        return false;
    }
    memset(new_buffer + request->content_size, 0, REQ_BUFF_SIZE + 1);
    request->buffer = new_buffer;
    return true;
}

bool request_append(request_t *request, const char *data, size_t size)
{
    size = size > REQ_BUFF_SIZE ? REQ_BUFF_SIZE : size;
    if (request->content_size + size > request->buffer_size) {
        if (!request_resize(request))
            return false;
    }
    memcpy(request->buffer + request->content_size, data, size);
    request->content_size += size;
    return true;
}
