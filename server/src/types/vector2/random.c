/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** random.c
*/

#include <stdlib.h>
#include "types/vector2.h"

vector2u_t vector2u_random(vector2u_t max)
{
    vector2u_t result = {0};

    result.x = random() % max.x;
    result.y = random() % max.y;
    return result;
}
