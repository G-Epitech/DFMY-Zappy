/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Node type free function
*/

#include <stdlib.h>
#include "types/node.h"

void node_free(node_t *node, node_freer_t freer)
{
    if (!node)
        return;
    if (freer)
        freer(node->data);
    free(node);
}
