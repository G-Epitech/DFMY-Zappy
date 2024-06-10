/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Egg free
*/

#include "types/egg.h"

void egg_free(egg_t *egg)
{
    if (egg)
        free(egg);
}

void egg_free_as_node_data(void *data)
{
    egg_free((egg_t *)data);
}
