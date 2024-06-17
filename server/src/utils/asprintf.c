/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** asprintf.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int my_asprintf(char **strp, const char *fmt, ...)
{
    va_list args1;
    va_list args2;
    int size = 0;

    va_start(args1, fmt);
    va_start(args2, fmt);
    size = vsnprintf(NULL, 0, fmt, args1) + 1;
    *strp = malloc(size);
    if (*strp)
        vsprintf(*strp, fmt, args2);
    else
        size = -1;
    va_end(args1);
    va_end(args2);
    return size;
}
