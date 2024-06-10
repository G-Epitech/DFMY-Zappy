/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** free.c
*/

#include <stdlib.h>
#include "types/emission.h"

void emission_free(emission_t *emission)
{
    if (!emission)
        return;
    free(emission->buffer);
    free(emission);
}

void emission_free_as_node_data(node_data_t data)
{
    emission_free(NODE_DATA_TO_PTR(data, emission_t *));
}
