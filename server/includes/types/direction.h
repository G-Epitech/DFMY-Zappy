/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** direction.h
*/

#pragma once

// @brief Structure representing a Trantorian direction
typedef enum direction_e {
    // @brief North direction
    DIR_NORTH = 1,
    // @brief East direction
    DIR_EAST,
    // @brief South direction
    DIR_SOUTH,
    // @brief West direction
    DIR_WEST
} direction_t;

/**
 * @brief Get the move vector of a direction
 * @param direction Direction to get the move vector
 * @return Move vector of the direction
 */
vector2l_t direction_get_move_vector(direction_t direction);
