/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** add.c
*/

#include "types/trantor/team.h"
#include "types/trantor/egg.h"

bool team_add_egg(team_t *team, egg_t *egg)
{
    node_data_t data = NODE_DATA_FROM_PTR(egg);

    if (!list_push(team->eggs, data))
        return false;
    egg->team = team;
    return true;
}

void team_remove_egg(team_t *team, egg_t *egg)
{
    node_data_t data = NODE_DATA_FROM_PTR(egg);
    node_t *node = team ? list_find(team->eggs, data) : NULL;

    if (node)
        list_erase(team->eggs, node, &egg_free_as_node_data);
    else
        egg_free(egg);
}

egg_t *team_get_random_egg(team_t *team)
{
    size_t index = team->eggs->len ? random() % team->eggs->len : 0;
    node_t *node = team->eggs->first;
    egg_t *egg = NULL;

    if (!node)
        return NULL;
    for (size_t i = 0; i < index; i++)
        node = node->next;
    egg = NODE_TO_PTR(node, egg_t *);
    return egg;
}
