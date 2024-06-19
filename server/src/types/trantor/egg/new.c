/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Egg new
*/

#include "types/trantor/egg.h"

void egg_init(egg_t *egg, team_t *team, vector2u_t position)
{
    egg->team = team;
    egg->position = position;
    egg->id = 0;
}

egg_t *egg_new(team_t *team, vector2u_t position)
{
    egg_t *egg = calloc(1, sizeof(egg_t));

    if (!egg)
        return NULL;
    egg_init(egg, team, position);
    return egg;
}
