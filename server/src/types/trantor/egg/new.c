/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Egg new
*/

#include "types/trantor/egg.h"

void egg_init(egg_t *egg)
{
    egg->team = NULL;
    egg->position.x = 0;
    egg->position.y = 0;
    egg->id = 0;
}

egg_t *egg_new(void)
{
    egg_t *egg = calloc(1, sizeof(egg_t));

    if (!egg)
        return NULL;
    egg_init(egg);
    return egg;
}
