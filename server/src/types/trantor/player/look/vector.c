/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** vector.c
*/

#include "types/trantor/player.h"

void player_look_vector(player_t *player, vector2l_t *look_vector)
{
    switch (player->direction) {
        case DIR_NORTH:
            look_vector->x = 1;
            look_vector->y = 1;
            break;
        case DIR_EAST:
            look_vector->x = 1;
            look_vector->y = -1;
            break;
        case DIR_SOUTH:
            look_vector->x = -1;
            look_vector->y = -1;
            break;
        default:
            look_vector->x = -1;
            look_vector->y = 1;
            break;
    }
}
