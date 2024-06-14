/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/list.h"
#include "types/controller.h"

void controller_init(controller_t *controller, int socket)
{
    controller->generic.type = CTRL_UNKNOWN;
    controller->generic.socket = socket;
}

controller_t *controller_new(int socket)
{
    controller_t *controller = calloc(1, sizeof(controller_t));
    list_t *requests = controller ? list_new() : NULL;
    list_t *emissions = controller ? list_new() : NULL;

    if (!controller)
        return NULL;
    controller->generic.requests = requests;
    controller->generic.emissions = emissions;
    if (!requests || !emissions) {
        controller_free(controller);
        return NULL;
    }
    controller_init(controller, socket);
    return controller;
}
