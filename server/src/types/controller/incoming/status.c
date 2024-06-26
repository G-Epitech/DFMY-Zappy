/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** player.c
*/

#include "types/controller.h"

bool controller_incoming_buffer_is_full(controller_t *controller)
{
    return buffer_is_full(controller->generic.incoming);
}