/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** usage_tests.c
*/

#include <criterion/criterion.h>
#include "app.h"

Test(stop_tests, app_exit)
{
    app_t app;

    app_init(&app);
    cr_assert_eq(app_exit(&app, 0), 0);
}

Test(stop_tests, app_stop)
{
    app_t app;

    // Arrange
    app_init(&app);
    app_sig_handlers_target(&app, true);

    // Act
    app_stop();

    // Assert
    cr_assert_eq(app.running, false);

    // Cleanup
    app_sig_handlers_target(NULL, true);
}

Test(stop_tests, app_stop_null_target)
{
    app_t app;

    // Arrange
    app_init(&app);
    app_sig_handlers_target(NULL, true);

    // Act
    app_stop();

    // Assert
    cr_assert_eq(app.running, true);

    // Cleanup
    app_sig_handlers_target(NULL, true);
}
