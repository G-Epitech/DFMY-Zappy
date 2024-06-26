/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Player new
*/

#include <memory.h>
#include "types/trantor/player.h"

void player_init(player_t *player, size_t id)
{
    memset(player->inventory, 0, RES_LEN * sizeof(size_t));
    player->controller = NULL;
    player->team = NULL;
    player->level = 1;
    player->inventory[RES_FOOD] = 10;
    player->lives = PLAYER_LIFE_UNITS_PER_FOOD * player->inventory[RES_FOOD];
    player->position = (vector2u_t) { 0, 0 };
    player->direction = PLAYER_DIRECTION_DEFAULT;
    player->id = id;
    player->incantation = NULL;
}

player_t *player_new(size_t id)
{
    player_t *player = calloc(1, sizeof(player_t));

    if (!player)
        return NULL;
    player_init(player, id);
    return player;
}
