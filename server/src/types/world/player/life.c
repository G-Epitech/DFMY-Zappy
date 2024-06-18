/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** update.c
*/

#include "types/world/player.h"
#include "types/world/chrono.h"

void player_update_lives(player_t *player, time_unit_t time_units)
{
    player->lives = time_units;
    if (player->lives <= 0) {
        player->lives = 0;
        player->inventory[RES_FOOD] = 0;
        return;
    }
    player->inventory[RES_FOOD] =
        (size_t) player->lives / PLAYER_LIFE_UNITS_PER_FOOD;
}
