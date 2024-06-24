/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** look.c
*/

#include "types/trantor/player.h"
#include "types/trantor/map.h"

void player_get_look_vector(player_t *player, vector2l_t *look)
{
    switch (player->direction) {
        case DIR_NORTH:
            look->x = 1;
            look->y = -1;
            break;
        case DIR_EAST:
            look->x = 1;
            look->y = 1;
            break;
        case DIR_SOUTH:
            look->x = -1;
            look->y = 1;
            break;
        default:
            look->x = -1;
            look->y = -1;
            break;
    }
}

axis_t player_get_look_axis(player_t *player)
{
    if (player->direction == DIR_NORTH || player->direction == DIR_SOUTH)
        return AXIS_V;
    else
        return AXIS_H;
}
