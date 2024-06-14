/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/request.h"

void request_init(request_t *request)
{
    request->status = REQ_PENDING;
    request->buffer_size = REQUEST_BUFF_SIZE;
    request->content_size = 0;
}

request_t *request_new(void)
{
    request_t *request = calloc(1, sizeof(request_t));

    if (!request)
        return NULL;
    request->buffer = calloc(1, REQUEST_BUFF_SIZE);
    if (!request->buffer) {
        free(request);
        return NULL;
    }
    request_init(request);
    return request;
}
