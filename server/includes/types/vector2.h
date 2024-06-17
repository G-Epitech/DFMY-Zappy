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
 * @param max Max values for x and y
 * @return Randomized vector2u_t
 */
vector2u_t vector2u_random(vector2u_t max);
