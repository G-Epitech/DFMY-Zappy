/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** random.c
*/

#include <stdlib.h>
#include "types/vector2.h"

void vector2u_random(vector2u_t *out, vector2u_t *max)
{
    out->x = random() % max->x;
    out->y = random() % max->y;
}
