/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** List type append function
*/

#include "types/list.h"

void list_append(list_t *list, node_t *node)
{
    if (!node || !list)
        return;
    if (list->last != NULL) {
        node->next = list->last->next;
        list->last->next = node;
        node->prev = list->last;
    } else {
        node->next = list->first;
        list->first = node;
        node->prev = NULL;
    }
    list->last = node;
    list->last->next = NULL;
    list->len++;
}

bool list_push(list_t *list, node_data_t data)
{
    node_t *node = node_new(data);

    if (!node)
        return false;
    list_append(list, node);
    return true;
}
