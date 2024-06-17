/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** asprintf_tests.c
*/

#include <criterion/criterion.h>
#include "utils.h"
#include "clcc/modules/stdio.h"
#include "clcc/modules/stdlib.h"

Test(asprintf, test_asprintf)
{
    char *str = NULL;
    int ret = my_asprintf(&str, "Hello, %s", "world");
    cr_assert_eq(ret, 13);
    cr_assert_str_eq(str, "Hello, world");
    free(str);
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
