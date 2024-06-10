/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "types/chrono.h"

Test(chrono_init_tests, simple_init)
{
    chrono_t chrono = { 0 };

    chrono_init(&chrono, 10);
    cr_assert_eq(chrono.frequency, 10);
    cr_assert_eq(chrono.started_at.tv_sec, 0);
    cr_assert_eq(chrono.started_at.tv_usec, 0);
    cr_assert_eq(chrono.stopped_at.tv_sec, 0);
    cr_assert_eq(chrono.stopped_at.tv_usec, 0);
}
