/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/list.h"
#include "types/controller.h"

void controller_free(controller_t *controller)
{
    if (!controller)
        return;
    // TODO: replace freer with the correct free function
    list_free(controller->generic.requests, NULL);
    // TODO: replace freer with the correct free function
    list_free(controller->generic.emissions, NULL);
    free(controller);
}

void controller_free_as_node_data(node_data_t data)
{
    controller_free(NODE_DATA_TO_PTR(data, controller_t *));
}
