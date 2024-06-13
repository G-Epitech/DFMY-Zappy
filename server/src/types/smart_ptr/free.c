/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** dereference.c
*/

#include "types/smart_ptr.h"

void smart_ptr_free(smart_ptr_t *smart_ptr)
{
    if (!smart_ptr)
        return;
    smart_ptr->ref_count--;
    if (smart_ptr->ref_count == 0) {
        if (smart_ptr->destructor) {
            smart_ptr->destructor(smart_ptr->ptr);
        }
        free(smart_ptr);
    }
}
