/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/list.h"
#include "types/controller.h"
#include "types/request.h"

void controller_free(controller_t *controller)
{
    if (!controller)
        return;
    list_free(controller->player.requests, &request_free_as_node_data);
    buffer_free(controller->generic.emissions);
    buffer_free(controller->generic.incoming);
    free(controller);
}

void controller_free_as_node_data(node_data_t data)
{
    controller_free(NODE_DATA_TO_PTR(data, controller_t *));
}
