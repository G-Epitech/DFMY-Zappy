/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** complete.c
*/

#include "types/trantor/incantation.h"
#include "types/trantor/player.h"
#include "types/trantor/map.h"

bool incantation_get_location(incantation_t *incantation,
    vector2u_t *location)
{
    player_t *player = NULL;

    if (!incantation || !incantation->players->first)
        return false;
    player = NODE_TO_PTR(incantation->players->first, player_t *);
    location->x = player->position.x;
    location->y = player->position.y;
    return true;
}
