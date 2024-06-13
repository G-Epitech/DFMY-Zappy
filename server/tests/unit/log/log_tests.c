/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** log_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "log.h"

static void setup(void) {
    *log_level() = LOG_ERROR;
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(log_tests, simple_info_with_level_not_active, .init = setup)
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
    cr_assert_str_empty(buffer);
}

Test(log_tests, simple_info_with_level_active, .init = setup)
{
    char *msg = "This is a simple log message";
    FILE* local_stdout = cr_get_redirected_stdout();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));
    *log_level() = LOG_INFO;

    // Act and assert
    log_info("%s", msg);

    // Assert
    fflush(stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_not_empty(buffer);
}

Test(log_tests, simple_warn_with_level_active, .init = setup)
{
    char *msg = "This is a simple log message";
    FILE* local_stdout = cr_get_redirected_stdout();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));
    *log_level() = LOG_WARN;

    // Act and assert
    log_warn("%s", msg);

    // Assert
    fflush(stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_not_empty(buffer);
}

Test(log_tests, simple_warn_with_level_not_active, .init = setup)
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
    cr_assert_str_empty(buffer);
}

Test(log_tests, simple_error_with_level_active, .init = setup)
{
    char *msg = "This is a simple log message";
    FILE* local_stdout = cr_get_redirected_stderr();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));
    *log_level() = LOG_ERROR;

    // Act and assert
    log_error("%s", msg);

    // Assert
    fflush(stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_not_empty(buffer);
}

Test(log_tests, simple_error_with_level_not_active, .init = setup)
{
    char *msg = "This is a simple log message";
    FILE* local_stdout = cr_get_redirected_stdout();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));

    // Act and assert
    log_error("%s", msg);

    // Assert
    fflush(stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_empty(buffer);
}

Test(log_tests, simple_debug_with_level_active, .init = setup)
{
    char *msg = "This is a simple log message";
    FILE* local_stdout = cr_get_redirected_stdout();
    char buffer[10000];

    memset(buffer, 0, sizeof(buffer));
    *log_level() = LOG_DEBUG;

    // Act and assert
    log_debug("%s", msg);

    // Assert
    fflush(stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_not_empty(buffer);
}

Test(log_tests, simple_debug_with_level_not_active, .init = setup)
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
    cr_assert_str_empty(buffer);
}
