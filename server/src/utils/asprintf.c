/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** asprintf.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int my_vasprintf(char **strp, const char *fmt, va_list args)
{
    va_list copy;
    int len;

    va_copy(copy, args);
    len = vsnprintf(NULL, 0, fmt, copy);
    va_end(copy);
    if (len < 0)
        return -1;
    *strp = calloc(len + 1, sizeof(char));
    if (!*strp)
        return -1;
    va_copy(copy, args);
    len = vsnprintf(*strp, len + 1, fmt, copy);
    va_end(copy);
    if (len < 0) {
        free(*strp);
        return -1;
    }
    return len;
}

int my_asprintf(char **strp, const char *fmt, ...)
{
    va_list args;
    int size = 0;

    va_start(args, fmt);
    size = my_vasprintf(strp, fmt, args);
    va_end(args);
    return size;
}
