/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Egg new
*/

#include "types/trantor/egg.h"

void egg_init(egg_t *egg, long laid_by, size_t id)
{
    egg->team = NULL;
    egg->position.x = 0;
    egg->position.y = 0;
    egg->id = id;
    egg->laid_by = laid_by;
}

egg_t *egg_new(long laid_by, size_t id)
{
    egg_t *egg = calloc(1, sizeof(egg_t));

    if (!egg)
        return NULL;
    egg_init(egg, laid_by, id);
    return egg;
}
