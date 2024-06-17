/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** usage_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <thread_db.h>
#include <unistd.h>
#include <signal.h>
#include "app.h"
#include "clcc/modules/stdlib.h"
#include "clcc/modules/sys/socket.h"

static void *thread_stopper_routine(void *seconds)
{
    double sec = *(double *) seconds;

    usleep((unsigned int) (sec * 1000000));
    kill(getpid(), SIGINT);
    return NULL;
}

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(run_tests, run_with_no_args, .init = cr_redirect_stderr)
{
    char *av[] = {"./zappy_server"};
    int ac = 1;

    cr_assert_eq(app_start(ac, av), APP_EXIT_FAILURE);
}

Test(run_tests, run_with_help, .init = redirect_all_stdout)
{
    FILE* local_stdout = cr_get_redirected_stdout();
    char *av[] = {"./zappy_server", "-h"};
    char buffer[10000];
    int ac = 2;

    memset(buffer, 0, sizeof(buffer));

    cr_assert_eq(app_start(ac, av), APP_EXIT_SUCCESS);
    fflush(stdout);
    fflush(local_stdout);
    fread(buffer, sizeof(char), sizeof(buffer), local_stdout);
    cr_assert_str_not_empty(buffer);
}

Test(run_tests, run_with_all_valid_arguments, .init = redirect_all_stdout)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "10", "-f", "100"};
    int ac = 14;
    double seconds = 0.1;
    thread_t thread;

    pthread_create(&thread, NULL, thread_stopper_routine, &seconds);
    cr_assert_eq(app_start(ac, av), APP_EXIT_SUCCESS);
    pthread_join(thread, NULL);
}

Test(run_tests, run_with_invalid_arguments, .init = cr_redirect_stderr)
{
    char *av[] = {"./zappy_server",
        "-p", "4242",
        "-x", "10",
        "-y", "10",
        "-n", "team1", "team2",
        "-c", "10",
        "-f", "100",
        "-t", "10"
    };
    int ac = 16;

    cr_assert_eq(app_start(ac, av), APP_EXIT_FAILURE);
    cr_assert_stderr_eq_str("Invalid flag: -t\n");
}

Test(run_tests, run_with_missing_port, .init = cr_redirect_stderr)
{
    char *av[] = {"./zappy_server",
        "-x", "10",
        "-y", "10",
        "-n", "team1", "team2",
        "-c", "10",
        "-f", "100",
    };
    int ac = 12;

    cr_assert_eq(app_start(ac, av), APP_EXIT_FAILURE);
    fflush(stderr);
    cr_assert_stderr_eq_str("Missing server port\n");
}

Test(run_tests, run_with_teams_as_last_args, .init = cr_redirect_stderr)
{
    char *av[] = {"./zappy_server",
        "-p", "4242",
        "-x", "10",
        "-y", "10",
        "-c", "10",
        "-f", "100",
        "-n", "team1", "team2", "team2"
    };
    int ac = 15;

    cr_assert_eq(app_start(ac, av), APP_EXIT_FAILURE);
    fflush(stderr);
    cr_assert_stderr_eq_str("Duplicated team name 'team2'\n");
}

Test(run_tests, run_fail_due_to_server_creation, .init = cr_redirect_stderr)
{
    char *av[] = {"./zappy_server",
        "-p", "4242",
        "-x", "10",
        "-y", "10",
        "-n", "team1", "team2",
        "-c", "10",
        "-f", "100",
    };
    int ac = 14;
    int status;

    clcc_return_value_after(calloc, NULL, 1);
    clcc_enable_control(calloc);
    status = app_start(ac, av);
    clcc_disable_control(calloc);
    cr_assert_eq(status, APP_EXIT_FAILURE);
    cr_assert_stderr_eq_str("Failed to create server\n");
}

Test(run_tests, run_fail_due_to_bind, .init = cr_redirect_stderr)
{
    char *av[] = {"./zappy_server",
        "-p", "4242",
        "-x", "10",
        "-y", "10",
        "-n", "team1", "team2",
        "-c", "10",
        "-f", "100",
    };
    int ac = 14;
    int status;

    clcc_return_now(bind, -1);
    status = app_start(ac, av);
    clcc_disable_control(bind);
    cr_assert_eq(status, APP_EXIT_FAILURE);
}