/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** vector2.h
*/

#pragma once

#include <stddef.h>

typedef struct vector2u_s {
    size_t x;
    size_t y;
} vector2u_t;

/**
 * @brief Get a random vector2u_t
 * @brief out The output vector2u_t
 * @brief max The maximum values for the random vector2u_t
 */
void vector2u_random(vector2u_t *out, vector2u_t *max);
