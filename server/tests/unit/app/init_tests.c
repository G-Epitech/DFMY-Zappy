/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** usage_tests.c
*/

#include <criterion/criterion.h>
#include <termios.h>
#include <unistd.h>
#include "app.h"

#include "clcc/modules/unistd.h"

Test(app_init_tests, app_init)
{
    app_t app;

    app_init(&app);
    cr_assert_eq(app.running, true);
    cr_assert_eq(app.server, NULL);
    cr_assert_eq(app.args.port, -1);
    cr_assert_eq(app.args.width, 0);
    cr_assert_eq(app.args.height, 0);
    cr_assert_eq(app.args.teams, NULL);
}

Test(app_init_tests, app_sig_handlers_target)
{
    app_t app;
    app_t *target;

    // Arrange
    app_init(&app);
    app_sig_handlers_target(NULL, true);

    // Act and Assert
    target = app_sig_handlers_target(NULL, false);
    cr_assert_null(target);
    target = app_sig_handlers_target(&app, true);
    cr_assert_eq(target, &app);
    target = app_sig_handlers_target(NULL, false);
    cr_assert_eq(target, &app);

    // Cleanup
    app_sig_handlers_target(NULL, true);
}

Test(app_init_tests, app_setup_sig_handlers)
{
    // Arrange
    struct termios term = { 0 };

    // Act
    clcc_return_now(isatty, 1);
    app_setup_sig_handlers();
    clcc_disable_control(isatty);
    tcgetattr(STDIN_FILENO, &term);

    // Assert
    cr_assert_eq(term.c_lflag & ECHOCTL, 0);
}

Test(app_init_tests, app_setup_sig_handlers_on_a_non_tty)
{
    // Arrange
    struct termios term = { 0 };
    tcflag_t flags;

    tcgetattr(STDIN_FILENO, &term);
    flags = term.c_lflag;

    // Act
    clcc_return_now(isatty, 0);
    app_setup_sig_handlers();
    clcc_disable_control(isatty);
    tcgetattr(STDIN_FILENO, &term);

    // Assert
    cr_assert_eq(term.c_lflag, flags);
}
