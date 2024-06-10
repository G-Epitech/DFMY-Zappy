/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** List type new function
*/

#include <stdlib.h>
#include "types/list.h"

void list_init(list_t *list)
{
    list->first = NULL;
    list->last = NULL;
    list->len = 0;
}
