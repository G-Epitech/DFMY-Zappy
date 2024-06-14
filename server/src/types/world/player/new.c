/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Player new
*/

#include <memory.h>
#include "types/world/player.h"

void player_init(player_t *player, player_controller_t *controller,
    team_t *team, vector2u_t position)
{
    player->controller = controller;
    player->team = team;
    player->level = 1;
    player->inventory[RES_FOOD] = 10;
    player->lives = PLAYER_LIFE_UNITS_PER_FOOD * player->inventory[RES_FOOD];
    player->position = position;
    memset(player->inventory, 0, RES_LEN * sizeof(size_t));
}

player_t *player_new(player_controller_t *controller, team_t *team,
    vector2u_t position)
{
    player_t *player = calloc(1, sizeof(player_t));

    if (!player)
        return NULL;
    player_init(player, controller, team, position);
    return player;
}
