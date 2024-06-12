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

static void log_handle_level(log_level_t level, FILE *stream)
{
    switch (level) {
        case WARN:
            fprintf(stream, "\033[1;33m[WARN] \033[0m");
            break;
        case ERROR:
            fprintf(stream, "\033[1;31m[ERROR] \033[0m");
            break;
        case DEBUG:
            fprintf(stream,"\033[1;34m[DEBUG] \033[0m");
            break;
        default:
            fprintf(stream,"\033[1;32m[INFO] \033[0m");
            break;
    }
}

static void log_current_time(FILE *stream)
{
    time_t now = 0;
    struct tm *local = NULL;

    time(&now);
    local = localtime(&now);
    fprintf(stream, "\033[3;90m%02d:%02d:%02d\033[0m ",
        local->tm_hour,
        local->tm_min,
        local->tm_sec
    );
}

static void log_message(log_level_t level, const char *format,
    va_list args)
{
    FILE *stream = level == ERROR ? stderr : stdout;

    log_current_time(stream);
    log_handle_level(level, stream);
    vfprintf(stream, format, args);
    fputc('\n', stream);
    fflush(stream);
}

void log_debug(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    log_message(DEBUG, format, args);
    va_end(args);
}

void log_info(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    log_message(INFO, format, args);
    va_end(args);
}

void log_warn(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    log_message(WARN, format, args);
    va_end(args);
}

void log_error(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    log_message(ERROR, format, args);
    va_end(args);
}
