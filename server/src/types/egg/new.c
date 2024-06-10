/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Egg new
*/

#include "types/egg.h"

egg_t *egg_new(team_t *team, vector2u_t position)
{
    egg_t *egg = calloc(1, sizeof(egg_t));

    if (!egg)
        return NULL;
    egg->team = team;
    egg->position = position;
    egg->id = 0;
    return egg;
}
