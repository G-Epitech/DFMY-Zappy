/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** new.c
*/

#include <stdlib.h>
#include "types/emission.h"

emission_t *emission_new(char *buffer, size_t buffer_size)
{
    emission_t *emission = calloc(1, sizeof(emission_t));

    if (!emission) {
        free(buffer);
        return NULL;
    }
    emission->buffer = buffer;
    emission->buffer_size = buffer_size;
    return emission;
}
