/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** List type append function
*/

#include "types/list.h"

bool list_some(list_t *list, list_predicate_t predicate)
{
    node_t *node = list ? list->first : NULL;

    while (node) {
        if (predicate(node->data))
            return true;
        node = node->next;
    }
    return false;
}
