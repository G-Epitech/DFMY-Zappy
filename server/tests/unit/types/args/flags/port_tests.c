/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "types/args.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(args_port_flags_tests, short_flag)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-p", "15"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_port(&parser, &args), true,
        "args_parse_port should return true"
    );
    cr_assert_eq(args.port, 15, "Port number should be equal to 15");
}

Test(args_port_flags_tests, long_flag)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--port", "15"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_port(&parser, &args), true,
        "args_parse_port should return true"
    );
    cr_assert_eq(args.port, 15, "Port number should be 15");
}

Test(args_port_flags_tests, too_little_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--port", "-78"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_port(&parser, &args), true,
        "args_parse_port should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.port, -78, "Server port should be equal to -78");
    cr_assert_stderr_eq_str("Server port must be between in range [0, 65535]\n");
}

Test(args_port_flags_tests, too_big_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--port", "65539"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_port(&parser, &args), true,
        "args_parse_port should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.port, 65539, "Port number should be equal to 65539");
    cr_assert_stderr_eq_str("Server port must be between in range [0, 65535]\n");
}

Test(args_port_flags_tests, invalid_number, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--port", "invalid"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_port(&parser, &args), true,
        "args_parse_port should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Invalid server port\n");
}

Test(args_port_flags_tests, missing_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--port"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_port(&parser, &args), true,
        "args_parse_port should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Missing value for server port\n");
}

Test(args_port_flags_tests, already_parsed_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-p", "12", "-p", "17"};
    args_parser_t parser = {5, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_port(&parser, &args), true,
        "args_parse_port should return true"
    );
    cr_assert_eq(parser.error, false, "parser.error should be false");
    parser.current += 1;
    cr_assert_eq(args_parse_port(&parser, &args), true,
        "args_parse_port should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Server port already set\n");
}

Test(args_port_flags_tests, not_port_flag)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--custom", "12"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_port(&parser, &args), false,
        "args_parse_port should return false"
    );
}
