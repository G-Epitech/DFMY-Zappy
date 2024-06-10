/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Node type unlink function
*/

#include "types/node.h"

void node_unlink(node_t *node)
{
    if (node->next)
        node->next->prev = node->prev;
    if (node->prev)
        node->prev->next = node->next;
}
