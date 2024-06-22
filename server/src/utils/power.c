/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** power.c
*/


#include <math.h>
#include "utils.h"

bool is_pow_of_two(unsigned int n)
{
    return (n && !(n & (n - 1)));
}

unsigned int nearest_pow_of_two(unsigned int n)
{
    unsigned int lower;
    unsigned int upper;

    if (is_pow_of_two(n))
        return n;
    lower = (unsigned int) pow(2, floor(log2(n)));
    upper = (unsigned int) pow(2, ceil(log2(n)));
    if ((n - lower) < (upper - n)) {
        return lower;
    } else {
        return upper;
    }
}
