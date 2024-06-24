/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** merge.c
*/

#include <stdlib.h>
#include "types/list.h"

void list_merge(list_t *dest, list_t *src)
{
    if (src->len == 0)
        return;
    if (dest->len == 0) {
        *dest = *src;
        list_init(src);
        return;
    }
    dest->last->next = src->first;
    src->first->prev = dest->last;
    dest->last = src->last;
    dest->len += src->len;
    list_init(src);
}
