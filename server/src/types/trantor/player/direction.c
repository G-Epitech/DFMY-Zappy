/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** direction.c
*/

#include "types/trantor/player.h"

void player_change_direction(player_t *player, int direction_offset)
{
    if (direction_offset != 1 && direction_offset != -1)
        return;
    player->direction = (player->direction + direction_offset) % 4;
    if (player->direction <= 0)
        player->direction = DIR_WEST;
}
