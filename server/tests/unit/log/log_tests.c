/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** log_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "log.h"

Test(log_tests, simple_info, .init = cr_redirect_stdout)
{
    char *msg = "This is a simple log message";
    FILE* local_stdout = cr_get_redirected_stdout();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));

    // Act and assert
    log_info("%s", msg);

    // Assert
    fflush(stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_not_empty(buffer);
}

Test(log_tests, simple_warn, .init = cr_redirect_stdout)
{
    char *msg = "This is a simple log message";
    FILE* local_stdout = cr_get_redirected_stdout();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));

    // Act and assert
    log_warn("%s", msg);

    // Assert
    fflush(stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_not_empty(buffer);
}

Test(log_tests, simple_error, .init = cr_redirect_stderr)
{
    char *msg = "This is a simple log message";
    FILE* local_stderr = cr_get_redirected_stderr();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));

    // Act and assert
    log_error("%s", msg);

    // Assert
    fflush(stderr);
    fread(buffer, sizeof(char), sizeof(buffer), local_stderr);
    cr_assert_str_not_empty(buffer);
}

Test(log_tests, simple_debug, .init = cr_redirect_stdout)
{
    char *msg = "This is a simple log message";
    FILE* local_stdout = cr_get_redirected_stdout();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));

    // Act and assert
    log_debug("%s", msg);

    // Assert
    fflush(stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_not_empty(buffer);
}
