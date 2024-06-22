/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** utils.h
*/

#pragma once

#include <stdbool.h>
#include <stdarg.h>

// @brief Macro to get the max value between two values
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// @brief Macro to get the min value between two values
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// @brief Macro to get the size of a string without
// the null-terminating character
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

/**
 * @brief Check if a number is a power of two
 * @param n Number to check
 * @return true if the number is a power of 2, false otherwise
 */
bool is_pow_of_two(unsigned int n);

/**
 * @brief Get the nearest power of two of a number
 * @param n Number to get the nearest power of
 * @return Nearest power of two of the number
 */
unsigned int nearest_pow_of_two(unsigned int n);
