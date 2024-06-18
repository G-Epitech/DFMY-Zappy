/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include "types/vector2.h"

Test(vector2, test_vector2_create)
{
    vector2u_t vec = {10, 10};
    vector2u_t vec2 = {10, 10};

    vector2u_random(&vec, &vec2);
    cr_assert_neq(vec.x, 0);
    cr_assert_neq(vec.y, 0);
    cr_assert_neq(vec.x, 10);
    cr_assert_neq(vec.y, 10);
}
