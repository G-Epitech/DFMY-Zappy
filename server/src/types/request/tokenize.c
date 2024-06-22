/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** append.c
*/

#include <memory.h>
#include "types/request.h"

size_t request_get_first_token_size(request_t *request)
{
    char *delim = NULL;

    delim = memchr(request->buffer, ' ', request->content_size);
    if (!delim)
        return request->content_size;
    return delim - request->buffer;
}
