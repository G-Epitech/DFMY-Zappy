/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** reference.c
*/

#include "types/smart_ptr.h"

smart_ptr_t *smart_ptr_reference(smart_ptr_t *smart_ptr)
{
    if (!smart_ptr)
        return NULL;
    smart_ptr->ref_count += 1;
    return smart_ptr;
}
