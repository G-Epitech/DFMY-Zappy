/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <stdlib.h>
#include "types/emission.h"

emission_t *emission_new(smart_ptr_t *buffer_ptr, size_t buffer_size,
    int flags)
{
    emission_t *emission = calloc(1, sizeof(emission_t));

    if (!emission) {
        return NULL;
    }
    emission->buffer_size = buffer_size;
    emission->written = 0;
    emission->buffer_ptr = smart_ptr_reference(buffer_ptr);
    emission->flags = flags;
    return emission;
}
