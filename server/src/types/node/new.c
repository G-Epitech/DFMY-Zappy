/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Node type new function
*/

#include <stdlib.h>
#include "types/node.h"

node_t *node_new(node_data_t data)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return NULL;
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
