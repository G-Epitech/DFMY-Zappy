/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** Egg free
*/

#include "types/trantor/egg.h"

void egg_free(egg_t *egg)
{
    free(egg);
}

void egg_free_as_node_data(node_data_t data)
{
    egg_free(NODE_DATA_TO_PTR(data, egg_t *));
}
