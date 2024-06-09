/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "types/args.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(args_clients_nb_flags_tests, short_flag)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-c", "15"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_clients_nb(&parser, &args), true,
        "args_parse_clients_nb should return true"
    );
    cr_assert_eq(args.clients_nb, 15, "Number of clients should be equal to 15");
}

Test(args_clients_nb_flags_tests, long_width)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--clients-nb", "15"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_clients_nb(&parser, &args), true,
        "args_parse_clients_nb should return true"
    );
    cr_assert_eq(args.clients_nb, 15, "Number of clients should be 15");
}

Test(args_clients_nb_flags_tests, too_little_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--clients-nb", "0"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_clients_nb(&parser, &args), true,
        "args_parse_clients_nb should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.clients_nb, 0, "Number of clients should be equal to 0");
    cr_assert_stderr_eq_str("Number of clients must be in range [1, 200]\n");
}

Test(args_clients_nb_flags_tests, too_big_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--clients-nb", "2000"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_clients_nb(&parser, &args), true,
        "args_parse_clients_nb should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.clients_nb, 2000, "Number of clients should be equal to 2000");
    cr_assert_stderr_eq_str("Number of clients must be in range [1, 200]\n");
}

Test(args_clients_nb_flags_tests, invalid_number, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--clients-nb", "invalid"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_clients_nb(&parser, &args), true,
        "args_parse_clients_nb should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Invalid number of clients\n");
}

Test(args_clients_nb_flags_tests, missing_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--clients-nb"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_clients_nb(&parser, &args), true,
        "args_parse_clients_nb should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Missing value for number of clients\n");
}

Test(args_clients_nb_flags_tests, already_parsed_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-c", "12", "-c", "17"};
    args_parser_t parser = {5, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_clients_nb(&parser, &args), true,
        "args_parse_clients_nb should return true"
    );
    cr_assert_eq(parser.error, false, "parser.error should be false");
    parser.current += 1;
    cr_assert_eq(args_parse_clients_nb(&parser, &args), true,
        "args_parse_clients_nb should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Number of clients already set\n");
}

Test(args_clients_nb_flags_tests, neither_width_or_height)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--custom", "12"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_clients_nb(&parser, &args), false,
        "args_parse_clients_nb should return false"
    );
}

