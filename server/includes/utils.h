/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** utils.h
*/

#pragma once

/**
 * @brief Allocates memory and copies the formatted string given in parameter
 * @param strp The buffer to copy the formatted string into
 * @param fmt Format string
 * @param ... Arguments to format
 * @return The number of characters copied
 */
int my_asprintf(char **strp, const char *fmt, ...);
