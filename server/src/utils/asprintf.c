/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** asprintf.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static int run_asprintf(char **strp, const char *fmt, va_list ap)
{
    va_list ap_copy;
    int len;

    va_copy(ap_copy, ap);
    len = vsnprintf(NULL, 0, fmt, ap_copy);
    va_end(ap_copy);
    if (len < 0)
        return -1;
    *strp = malloc(len + 1);
    if (!*strp)
        return -1;
    va_copy(ap_copy, ap);
    len = vsnprintf(*strp, len + 1, fmt, ap_copy);
    va_end(ap_copy);
    if (len < 0) {
        free(*strp);
        return -1;
    }
    return len;
}

int my_asprintf(char **strp, const char *fmt, ...)
{
    va_list ap;
    int len;

    if (!strp || !fmt)
        return -1;
    va_start(ap, fmt);
    len = run_asprintf(strp, fmt, ap);
    va_end(ap);
    return len;
}
