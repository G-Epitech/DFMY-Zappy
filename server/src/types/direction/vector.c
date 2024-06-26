/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** vector.c
*/

#include "types/vector2.h"
#include "types/direction.h"

vector2l_t direction_get_move_vector(direction_t direction)
{
    vector2l_t move_vector = { 0, 0 };

    switch (direction) {
        case DIR_NORTH:
            move_vector.y = 1;
            break;
        case DIR_SOUTH:
            move_vector.y = -1;
            break;
        case DIR_WEST:
            move_vector.x = -1;
            break;
        default:
            move_vector.x = 1;
            break;
    }
    return move_vector;
}
