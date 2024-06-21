/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** clear.c
*/

#include "types/controller.h"

void controller_clear_first_request(controller_t *controller)
{
    list_t *requests = NULL;
    node_t *request = NULL;

    if (!controller)
        return;
    requests = controller->generic.requests;
    request = requests->first;
    if (request)
        list_erase(requests, request, &request_free_as_node_data);
}
