/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** update.c
*/

#include "math.h"
#include "types/world/player.h"
#include "types/world/chrono.h"

void player_update_lives(player_t *player, time_unit_t time_units)
{
    player->lives = time_units;
    player->inventory[RES_FOOD] =
        (size_t) ceilf(player->lives / PLAYER_LIFE_UNITS_PER_FOOD);
}
