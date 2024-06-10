/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** usage_tests.c
*/

#include <criterion/criterion.h>
#include "app.h"

Test(stop_tests, get_value_of_stopped)
{
    cr_assert_eq(*app_stopped(), false);
}

Test(stop_tests, set_value_of_stopped)
{
    cr_assert_eq(*app_stopped(), false);
    app_stop();
    cr_assert_eq(*app_stopped(), true);
}

Test(stop_tests, app_running_macro_must_return_true)
{
    *app_stopped() = false;
    cr_assert_eq(APP_RUNNING, true);
}

Test(stop_tests, app_running_macro_must_return_false)
{
    app_stop();
    cr_assert_eq(APP_RUNNING, false);
}
