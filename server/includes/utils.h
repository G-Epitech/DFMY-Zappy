/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** utils.h
*/

#pragma once

#include <stdarg.h>

#define STR_STRICT_SIZEOF(s) (sizeof(s) - 1)

// @brief Time value
typedef struct timeval timeval_t;

/**
 * @brief Allocates memory and copies the formatted string given in parameter
 * @param strp The buffer to copy the formatted string into
 * @param fmt Format string
 * @param ... Arguments to format
 * @return The number of characters copied
 */
int my_asprintf(char **strp, const char *fmt,
    ...) __attribute__((format(printf, 2, 3)));

/**
 * @brief Allocates memory and copies the formatted string given in parameter
 * @param strp The buffer to copy the formatted string into
 * @param fmt Format string
 * @param args Arguments to format
 * @return The number of characters copied
 */
int my_vasprintf(char **strp, const char *fmt, va_list args)
__attribute__((format(printf, 2, 0)));
