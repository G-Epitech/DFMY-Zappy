/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** List type free function
*/

#include <stdlib.h>
#include "types/list.h"

void list_clear(list_t *list, node_freer_t freer)
{
    node_t *node = list ? list->first : NULL;
    node_t *next = NULL;

    while (list && node) {
        next = node->next;
        node_free(node, freer);
        list->len -= 1;
        node = next;
    }
}

void list_free(list_t *list, node_freer_t freer)
{
    list_clear(list, freer);
    free(list);
}
