/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "types/args.h"

Test(args_init_tests, simple_init)
{
    args_t args = { 0 };

    args_init(&args);
    cr_assert_eq(args.port, -1);
    cr_assert_eq(args.width, 0);
    cr_assert_eq(args.height, 0);
    cr_assert_eq(args.clients_nb, 0);
    cr_assert_eq(args.frequency, ARGS_DEFAULT_FREQ);
    cr_assert_eq(args.verbose_level, ARGS_DEFAULT_VERBOSE_LEVEL);
    cr_assert_eq(args.teams, NULL);
}

Test(args_free_tests, free_no_teams)
{
    args_t args = { 0 };

    args_init(&args);
    cr_assert_eq(args.port, -1);
    cr_assert_eq(args.width, 0);
    cr_assert_eq(args.height, 0);
    cr_assert_eq(args.clients_nb, 0);
    cr_assert_eq(args.frequency, ARGS_DEFAULT_FREQ);
    cr_assert_eq(args.verbose_level, ARGS_DEFAULT_VERBOSE_LEVEL);
    cr_assert_eq(args.teams, NULL);
    args_free(&args);
}

Test(args_free_tests, free_with_teams)
{
    args_t args = { 0 };

    args_init(&args);
    cr_assert_eq(args.port, -1);
    cr_assert_eq(args.width, 0);
    cr_assert_eq(args.height, 0);
    cr_assert_eq(args.clients_nb, 0);
    cr_assert_eq(args.frequency, ARGS_DEFAULT_FREQ);
    cr_assert_eq(args.verbose_level, ARGS_DEFAULT_VERBOSE_LEVEL);
    cr_assert_eq(args.teams, NULL);
    args.teams = malloc(sizeof(char *) * 2);
    args_free(&args);
}

Test(args_parse_tests, parse_no_args)
{
    args_t args = { 0 };
    char *argv[] = { "./zappy_server" };
    int argc = 1;

    args_init(&args);
    cr_assert_eq(args_parse(argc, argv, &args), true);
}

Test(args_parse_tests, parse_invalid_flag, .init = cr_redirect_stderr)
{
    args_t args = { 0 };
    char *argv[] = { "./zappy_server", "--custom-flag" };
    int argc = 2;

    args_init(&args);
    cr_assert_eq(args_parse(argc, argv, &args), false);
    cr_assert_stderr_eq_str("Invalid flag: --custom-flag\n");
}

Test(args_parse_tests, parse_invalid_arg, .init = cr_redirect_stderr)
{
    args_t args = { 0 };
    char *argv[] = { "./zappy_server", "invalid_arg" };
    int argc = 2;

    args_init(&args);
    cr_assert_eq(args_parse(argc, argv, &args), false);
    cr_assert_stderr_eq_str("Invalid argument: invalid_arg\n");
}

Test(args_parse_tests, parse_valid_flag)
{
    args_t args = { 0 };
    char *argv[] = { "./zappy_server", "-p", "4242" };
    int argc = 3;

    args_init(&args);
    cr_assert_eq(args_parse(argc, argv, &args), true);
    cr_assert_eq(args.port, 4242);
}

Test(args_parse_tests, parse_several_flags)
{
    args_t args = { 0 };
    char *argv[] = {
        "./zappy_server",
        "-p", "4242",
        "-x", "10",
        "-y", "10",
        "-c", "10",
        "-f", "10",
        "--teams", "team1", "team2", "team3"
    };
    int argc = 15;

    args_init(&args);
    cr_assert_eq(args_parse(argc, argv, &args), true);
    cr_assert_eq(args.port, 4242);
    cr_assert_eq(args.width, 10);
    cr_assert_eq(args.height, 10);
    cr_assert_eq(args.clients_nb, 10);
    cr_assert_eq(args.frequency, 10);
    cr_assert_str_eq(args.teams[0], "team1");
    cr_assert_str_eq(args.teams[1], "team2");
    cr_assert_str_eq(args.teams[2], "team3");
    args_free(&args);
}

Test(args_parse_tests, parse_several_flags_with_error, .init = cr_redirect_stderr)
{
    args_t args = { 0 };
    char *argv[] = {
        "./zappy_server",
        "-p", "4242",
        "-x", "10",
        "-y", "10",
        "-c", "qwerty",
        "-f", "10",
        "--teams", "team1", "team2", "team3"
    };
    int argc = 15;

    args_init(&args);
    cr_assert_eq(args_parse(argc, argv, &args), false);
    cr_assert_eq(args.port, 4242);
    cr_assert_eq(args.width, 10);
    cr_assert_eq(args.height, 10);
    cr_assert_eq(args.clients_nb, 0);
    cr_assert_eq(args.frequency, ARGS_DEFAULT_FREQ);
    cr_assert_null(args.teams);
    cr_assert_stderr_eq_str("Invalid number of clients\n");
    args_free(&args);
}

Test(args_valid_tests, all_args_are_valid)
{
    args_t args = { 0 };
    char *teams[] = { "team1", "team2", "team3", NULL };

    args_init(&args);
    args.port = 4242;
    args.width = 10;
    args.height = 10;
    args.clients_nb = 10;
    args.frequency = 10;
    args.teams = teams;
    cr_assert_eq(args_are_valid(&args), true);
}

Test(args_valid_tests, invalid_port, .init = cr_redirect_stderr)
{
    args_t args = { 0 };

    args_init(&args);
    cr_assert_eq(args_are_valid(&args), false);
    cr_assert_stderr_eq_str("Missing server port\n");
}

Test(args_valid_tests, invalid_map_width, .init = cr_redirect_stderr)
{
    args_t args = { 0 };

    args_init(&args);
    args.port = 4242;
    cr_assert_eq(args_are_valid(&args), false);
    cr_assert_stderr_eq_str("Missing map width\n");
}

Test(args_valid_tests, invalid_map_height, .init = cr_redirect_stderr)
{
    args_t args = { 0 };

    args_init(&args);
    args.port = 4242;
    args.width = 10;
    cr_assert_eq(args_are_valid(&args), false);
    cr_assert_stderr_eq_str("Missing map height\n");
}

Test(args_valid_tests, invalid_clients_nb, .init = cr_redirect_stderr)
{
    args_t args = { 0 };

    args_init(&args);
    args.port = 4242;
    args.width = 10;
    args.height = 10;
    cr_assert_eq(args_are_valid(&args), false);
    cr_assert_stderr_eq_str("Missing clients number\n");
}

Test(args_valid_tests, invalid_teams, .init = cr_redirect_stderr)
{
    args_t args = { 0 };

    args_init(&args);
    args.port = 4242;
    args.width = 10;
    args.height = 10;
    args.clients_nb = 10;
    cr_assert_eq(args_are_valid(&args), false);
    cr_assert_stderr_eq_str("Missing teams names\n");
}

Test(args_valid_tests, all_args_are_valid_with_help)
{
    args_t args = { 0 };
    char *teams[] = { "team1", "team2", "team3", NULL };

    args_init(&args);
    args.port = 4242;
    args.width = 10;
    args.height = 10;
    args.clients_nb = 10;
    args.frequency = 10;
    args.teams = teams;
    args.help = true;
    cr_assert_eq(args_are_valid(&args), true);
}
