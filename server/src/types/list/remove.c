/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** List type remove and delete function
*/

#include <stdlib.h>
#include <stdio.h>
#include "types/list.h"

void list_pop(list_t *list, node_t *node)
{
    node_unlink(node);
    if (list->first == node)
        list->first = node->next;
    if (list->first)
        list->first->prev = NULL;
    if (list->last == node)
        list->last = node->prev;
    if (list->last)
        list->last->next = NULL;
    list->len--;
}

void list_erase(list_t *list, node_t *node, node_freer_t freer)
{
    list_pop(list, node);
    node_free(node, freer);
}
