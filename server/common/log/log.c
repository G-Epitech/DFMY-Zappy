/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** log.c
*/

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdbool.h>
#include "log.h"

static void log_handle_level(log_level_t level)
{
    switch (level) {
        case INFO:
            printf("\033[1;32m[INFO] \033[0m");
            break;
        case WARN:
            printf("\033[1;33m[WARN] \033[0m");
            break;
        case ERROR:
            printf("\033[1;31m[ERROR] \033[0m");
            break;
        case DEBUG:
            printf("\033[1;34m[DEBUG] \033[0m");
            break;
    }
}

static void log_current_time(void)
{
    time_t now = 0;
    char buf[20] = {0};
    struct tm *local = NULL;

    time(&now);
    local = localtime(&now);
    strftime(buf, sizeof(buf), "%H:%M:%S", local);
    printf("\033[3;90m%s\033[0m ", buf);
}

void log_message(log_level_t level, const char *format, ...)
{
    va_list args;

    log_current_time();
    log_handle_level(level);
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}
