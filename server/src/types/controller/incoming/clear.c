/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** clear.c
*/

#include "types/controller.h"

void controller_clear_incoming_buffer(controller_t *controller)
{
    buffer_clear(controller->generic.incoming);
}
