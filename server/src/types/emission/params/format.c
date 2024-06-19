/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** format.c
*/

#include <stdarg.h>
#include "types/emission.h"
#include "utils.h"

bool emission_params_from_format(emission_params_t *params, int flags,
    const char *format, ...)
{
    va_list args;
    char *buffer = NULL;
    int size = 0;

    va_start(args, format);
    size = my_vasprintf(&buffer, format, args);
    va_end(args);
    if (size < 0)
        return false;
    params->buffer_size = size;
    params->buffer = buffer;
    params->flags = flags;
    return true;
}
