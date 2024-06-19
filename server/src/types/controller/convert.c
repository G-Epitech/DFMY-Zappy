/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** init.c
*/

#include "types/controller.h"
#include "types/trantor/player.h"
#include "types/vector2.h"

bool controller_player_from_generic(controller_t *controller, team_t *team,
    vector2u_t position)
{
    if (!controller || !team)
        return false;
    controller->player.type = CTRL_PLAYER;
    controller->player.cooldown = 0;
    controller->player.player = player_new((player_controller_t *) controller,
        team, position);
    if (!controller->player.player)
        return false;
    return true;
}
