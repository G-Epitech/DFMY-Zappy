/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** merge.c
*/

#include <stdlib.h>
#include "types/list.h"

static void list_reset(list_t *list)
{
    list->first = NULL;
    list->last = NULL;
    list->len = 0;
}

bool list_merge(list_t *dest, list_t *src)
{
    if (!dest || !src)
        return false;
    if (src->len == 0)
        return true;
    if (dest->len == 0) {
        *dest = *src;
        list_reset(src);
        return true;
    }
    dest->last->next = src->first;
    src->first->prev = dest->last;
    dest->last = src->last;
    dest->len += src->len;
    list_reset(src);
    return true;
}
