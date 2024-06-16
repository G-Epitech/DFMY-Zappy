/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** direction.c
*/

#include "types/world/player.h"

void player_change_direction(player_t *player, int direction_offset)
{
    int temp_direction;

    if (direction_offset != 90 && direction_offset != -90)
        return;
    temp_direction = ((int) player->direction + direction_offset);
    if (temp_direction >= 360)
        temp_direction = 0;
    else if (temp_direction < 0)
        temp_direction = 270;
    player->direction = (player_direction_t) temp_direction;
}
