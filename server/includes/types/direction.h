/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** direction.h
*/

#pragma once

// @brief Forward declaration of vector2l_t
typedef struct vector2l_s vector2l_t;

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

typedef struct direction_quadrant_s {
    // @brief Player direction
    direction_t direction;
    // @brief Quadrant of the player direction
    int quadrants[8];
} direction_quadrant_t;

/**
 * @brief Get the move vector of a direction
 * @param direction Direction to get the move vector
 * @return Move vector of the direction
 */
vector2l_t direction_get_move_vector(direction_t direction);

/**
 * @brief Reverse a direction
 * @param direction Direction to reverse
 * @return Reversed direction
 */
direction_t direction_reverse(direction_t direction);

/**
 * @brief Get the quadrant of a direction
 * @param direction Direction to get the quadrant
 * @param quadrant Quadrant to get
 * @return Quadrant of the direction
 */
int direction_get_quadrant(direction_t direction, int quadrant);
