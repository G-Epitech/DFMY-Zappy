/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** List type new function
*/

#include <stdlib.h>
#include "types/list.h"

node_t *list_find(list_t *list, node_data_t data)
{
    node_t *node = list->first;

    while (node) {
        if (node->data.ptr == data.ptr)
            return node;
        node = node->next;
    }
    return NULL;
}
