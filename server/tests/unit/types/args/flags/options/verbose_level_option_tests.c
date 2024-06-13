/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "types/args.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(args_options_verbose_level_tests, short_verbose)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-v", "INFO"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_verbose_level_option(&parser, &args), true,
        "args_parse_verbose_level_option should return true"
    );
    cr_assert_eq(args.verbose_level, LOG_INFO, "Verbose level should be equal to LOG_INFO");
}

Test(args_options_verbose_level_tests, long_verbose)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--verbose-level", "INFO"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_verbose_level_option(&parser, &args), true,
        "args_parse_verbose_level_option should return true"
    );
    cr_assert_eq(args.verbose_level, LOG_INFO, "Verbose level should be equal to LOG_INFO");
}

Test(args_options_verbose_level_tests, no_verbose)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--no-verbose-level"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_verbose_level_option(&parser, &args), false,
        "args_parse_verbose_level_option should return false"
    );
    cr_assert_eq(args.verbose_level, ARGS_DEFAULT_VERBOSE_LEVEL, "Verbose level should be equal to default verbose level");
}

Test(args_options_verbose_level_tests, no_verbose_level_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--verbose-level"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_verbose_level_option(&parser, &args), true,
        "args_parse_verbose_level_option should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.verbose_level, ARGS_DEFAULT_VERBOSE_LEVEL, "Verbose level should still be default value");
    cr_assert_stderr_eq_str("Missing value for verbose level\n");
}

Test(args_options_verbose_level_tests, invalid_level_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-v", "WERROR"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_verbose_level_option(&parser, &args), true,
        "args_parse_verbose_level_option should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.verbose_level, ARGS_DEFAULT_VERBOSE_LEVEL, "Verbose level should still be default value");
    cr_assert_stderr_eq_str("Invalid verbose level: WERROR\n");
}
