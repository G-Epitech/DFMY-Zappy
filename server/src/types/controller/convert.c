/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** init.c
*/

#include "types/controller.h"
#include "types/trantor/player.h"

bool controller_player_from_generic(controller_t *controller,
    player_t *player)
{
    if (!controller || !player)
        return false;
    controller->player.type = CTRL_PLAYER;
    controller->player.cooldown = 0;
    controller->player.player = player;
    player->controller = (player_controller_t *) controller;
    return true;
}

bool controller_graphic_from_generic(controller_t *controller)
{
    if (!controller)
        return false;
    controller->graphic.type = CTRL_GRAPHIC;
    return true;
}
