/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** log.c
*/

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include "log.h"

static void log_handle_level(log_level_t level, FILE *stream)
{
    switch (level) {
        case LOG_WARN:
            fprintf(stream, "\033[1;33m[WARN]  \033[0m");
            break;
        case LOG_ERROR:
            fprintf(stream, "\033[1;31m[ERROR] \033[0m");
            break;
        case LOG_DEBUG:
            fprintf(stream, "\033[1;34m[DEBUG] \033[0m");
            break;
        default:
            fprintf(stream, "\033[1;32m[INFO]  \033[0m");
            break;
    }
}

static void log_current_time(FILE *stream)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    time_t now = tv.tv_sec;
    struct tm *local = localtime(&now);
    fprintf(stream, "\033[3;90m%02d:%02d:%02d.%03ld\033[0m ",
        local->tm_hour,
        local->tm_min,
        local->tm_sec,
        tv.tv_usec / 1000
    );
}

static void log_message(log_level_t level, const char *format,
    va_list args)
{
    FILE *stream = level == LOG_ERROR ? stderr : stdout;

    if (level < *log_level())
        return;
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
    log_message(LOG_DEBUG, format, args);
    va_end(args);
}

void log_info(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    log_message(LOG_INFO, format, args);
    va_end(args);
}

void log_warn(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    log_message(LOG_WARN, format, args);
    va_end(args);
}

void log_error(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    log_message(LOG_ERROR, format, args);
    va_end(args);
}
