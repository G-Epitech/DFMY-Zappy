/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** smart_ptr.c
*/

#include "types/smart_ptr.h"

smart_ptr_t *smart_ptr_new(void *data)
{
    smart_ptr_t *smart_ptr = calloc(1, sizeof(smart_ptr_t));

    if (!smart_ptr)
        return NULL;
    smart_ptr->ptr = data;
    smart_ptr->ref_count = 0;
    smart_ptr->destructor = &free;
    return smart_ptr;
}
