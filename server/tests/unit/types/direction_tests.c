/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** direction_tests.c
*/

#include <criterion/criterion.h>
#include "types/direction.h"
#include "types/vector2.h"

Test(direction, test_direction_get_move_vector)
{
    vector2l_t vec = direction_get_move_vector(DIR_NORTH);

    cr_assert_eq(vec.x, 0);
    cr_assert_eq(vec.y, 1);
    vec = direction_get_move_vector(DIR_SOUTH);
    cr_assert_eq(vec.x, 0);
    cr_assert_eq(vec.y, -1);
    vec = direction_get_move_vector(DIR_WEST);
    cr_assert_eq(vec.x, -1);
    cr_assert_eq(vec.y, 0);
    vec = direction_get_move_vector(DIR_EAST);
    cr_assert_eq(vec.x, 1);
    cr_assert_eq(vec.y, 0);
}

Test(direction, test_direction_reverse)
{
    cr_assert_eq(direction_reverse(DIR_NORTH), DIR_SOUTH);
    cr_assert_eq(direction_reverse(DIR_SOUTH), DIR_NORTH);
    cr_assert_eq(direction_reverse(DIR_WEST), DIR_EAST);
    cr_assert_eq(direction_reverse(DIR_EAST), DIR_WEST);
}
