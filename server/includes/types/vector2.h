/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** vector2.h
*/

#pragma once

#include <stddef.h>

// @brief Used to cast a vector2u_t to a vector2i_t
#define VECTOR2L_FROM_U(vec) ((vector2l_t){(long)vec.x, (long)vec.y})
// @brief Used to cast a vector2i_t to a vector2u_t
#define VECTOR2U_FROM_L(vec) ((vector2u_t){(size_t)vec.x, (size_t)vec.y})

typedef struct vector2u_s {
    size_t x;
    size_t y;
} vector2u_t;

typedef struct vector2l_s {
    long x;
    long y;
} vector2l_t;

/**
 * @brief Get a random vector2u_t
 * @brief out The output vector2u_t
 * @brief max The maximum values for the random vector2u_t
 */
void vector2u_random(vector2u_t *out, vector2u_t *max);
