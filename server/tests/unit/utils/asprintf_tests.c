/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** asprintf_tests.c
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include "utils.h"
#include "clcc/modules/stdio.h"
#include "clcc/modules/stdlib.h"

Test(asprintf, test_asprintf)
{
    char *str = NULL;
    int ret = my_asprintf(&str, "Hello, %s", "world");
    cr_assert_eq(ret, 12);
    cr_assert_str_eq(str, "Hello, world");
    free(str);
}

Test(asprintf, test_asprintf_null)
{
    char *str = NULL;
    int ret = my_asprintf(&str, NULL);
    cr_assert_eq(ret, -1);
    cr_assert_null(str);
}

Test(asprintf, test_asprintf_null_str)
{
    char *str = NULL;
    int ret = my_asprintf(NULL, "Hello, %s", "world");
    cr_assert_eq(ret, -1);
    cr_assert_null(str);
}

Test(asprintf, test_asprintf_null_str_and_null)
{
    char *str = NULL;
    int ret = my_asprintf(NULL, NULL);
    cr_assert_eq(ret, -1);
    cr_assert_null(str);
}

Test(asprintf, test_vsnprintf_fail)
{
    char *str = NULL;
    int ret = 0;

    clcc_return_now(vsnprintf, -1);
    ret = my_asprintf(&str, "Hello, %s", "world");
    clcc_disable_control(vsnprintf);
    cr_assert_eq(ret, -1);
}

Test(asprintf, test_vsnprintf_fail_on_second_call)
{
    char *str = NULL;
    int ret = 0;

    clcc_return_value_after(vsnprintf, -1, 1);
    clcc_enable_control(vsnprintf);
    ret = my_asprintf(&str, "Hello, %s", "world");
    clcc_disable_control(vsnprintf);
    cr_assert_eq(ret, -1);
}

Test(asprintf, test_malloc_fail)
{
    char *str = NULL;
    int ret = 0;

    clcc_return_now(malloc, NULL);
    ret = my_asprintf(&str, "Hello, %s", "world");
    clcc_disable_control(malloc);
    cr_assert_eq(ret, -1);
}
