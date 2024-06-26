/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** append.c
*/

#include <memory.h>
#include "types/request.h"

static void get_next_token(char *start, size_t size, incoming_token_t *token)
{
    char *delim = NULL;

    token->content = start;
    token->size = size;
    delim = memchr(start, ' ', size);
    if (delim)
        token->size = (delim - start);
}

bool request_get_token(request_t *request, size_t index,
    incoming_token_t *token)
{
    char *start = request->buffer;
    size_t size = request->content_size;
    size_t i = 0;

    while (i < index && size > 0) {
        get_next_token(start, size, token);
        start += token->size + 1;
        size -= token->size;
        size -= (size > 0 ? 1 : 0);
        i += 1;
    }
    if (i != index || size == 0)
        return false;
    get_next_token(start, size, token);
    return true;
}
