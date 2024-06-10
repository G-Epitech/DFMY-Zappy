/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/request.h"

void request_free(request_t *request)
{
    if (!request)
        return;
    free(request->buffer);
    free(request);
}

void request_free_as_node_data(node_data_t request)
{
    request_free(NODE_DATA_TO_PTR(request, request_t *));
}
