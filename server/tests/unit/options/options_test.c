/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options parser
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "options/options.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(options_create, options_create)
{
    options_t *options = options_create();

    cr_assert_not_null(options);
    cr_assert_eq(options->port, -1);
    cr_assert_eq(options->width, -1);
    cr_assert_eq(options->height, -1);
    cr_assert_eq(options->clients_nb, -1);
    cr_assert_eq(options->freq, -1);
    cr_assert_null(options->teams);
}

Test(options_destroy, options_destroy)
{
    options_t *options = options_create();

    options_destroy(options);
}

Test(options_usage, options_usage, .init = cr_redirect_stdout)
{
    const char *expected_output =
            "USAGE: ./zappy_server -p port -x width -y height -n team1 team2 ... -c clients_nb -f freq\n"
            "option description\n"
            "-p port        port number (1024 <-> 65535)\n"
            "-x width       width of the world (10 <-> 30)\n"
            "-y height      height of the world (10 <-> 30)\n"
            "-n [teams]     name of the team (at least one)\n"
            "-c clients_nb   number of authorized clients per team (1 <-> 200)\n"
            "-f freq        reciprocal of time unit for execution of actions (2 <-> 10000)\n";

    print_usage();
    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output);
}

Test(options_parse, options_parse)
{
    char *argv[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "10", "-f", "100"};
    options_t *options = options_parse(14, argv);

    cr_assert_not_null(options);
    cr_assert_eq(options->port, 4242);
    cr_assert_eq(options->width, 10);
    cr_assert_eq(options->height, 10);
    cr_assert_eq(options->clients_nb, 10);
    cr_assert_eq(options->freq, 100);
    cr_assert_str_eq(options->teams[0], "team1");
    cr_assert_str_eq(options->teams[1], "team2");
    options_destroy(options);
}

Test(options_parse, options_parse_error, .init = redirect_all_stdout)
{
    char *argv[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-n", "-c", "10", "-f", "100"};
    options_t *options = options_parse(12, argv);

    cr_assert_null(options);
}
