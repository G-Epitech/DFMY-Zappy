/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include "types/world/incantation.h"

void incantation_free(incantation_t *incantation)
{
    if (!incantation)
        return;
    list_free(incantation->players, NULL);
    free(incantation);
}

void incantation_free_as_node_data(node_data_t incantation)
{
    incantation_free(NODE_DATA_TO_PTR(incantation, incantation_t *));
}
