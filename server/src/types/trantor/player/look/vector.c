/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** vector.c
*/

#include "types/trantor/player.h"

void player_look_vector(player_t *player, player_look_info_t *info)
{
    switch (player->direction) {
        case DIR_NORTH:
            info->vector.x = 1;
            info->vector.y = -1;
            break;
        case DIR_EAST:
            info->vector.x = 1;
            info->vector.y = 1;
            break;
        case DIR_SOUTH:
            info->vector.x = -1;
            info->vector.y = 1;
            break;
        default:
            info->vector.x = -1;
            info->vector.y = -1;
            break;
    }
}
