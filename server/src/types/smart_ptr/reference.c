/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** reference.c
*/

#include "types/smart_ptr.h"

void smart_ptr_reference(smart_ptr_t **new_ptr, smart_ptr_t **smart_ptr)
{
    if (!smart_ptr || !(*smart_ptr))
        return;
    (*(*smart_ptr)->ref_count)++;
    if (new_ptr) {
        *new_ptr = *smart_ptr;
    }
}
