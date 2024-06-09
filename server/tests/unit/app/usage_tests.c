/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** usage_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "app.h"

Test(usage_tests, simple_usage, .init = cr_redirect_stdout)
{
    FILE* local_stdout = cr_get_redirected_stdout();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));
    app_print_usage();
    fflush(stdout);
    fflush(local_stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_not_empty(buffer);
}
