/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** promote_graphic.c
*/

#include "app.h"

void app_promote_controller_to_graphic(app_t *app, controller_t *controller)
{
    controller->generic.type = CTRL_GRAPHIC;
}
