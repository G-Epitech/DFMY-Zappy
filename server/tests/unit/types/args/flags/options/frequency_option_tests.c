/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "types/args.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(args_options_freq_tests, short_freq)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-f", "10"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_frequency_option(&parser, &args), true,
        "args_parse_frequency_option should return true"
    );
    cr_assert_eq(args.frequency, 10, "Frequency should be equal to 10");
}

Test(args_options_freq_tests, long_freq)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--frequency", "10"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_frequency_option(&parser, &args), true,
        "args_parse_frequency_option should return true"
    );
    cr_assert_eq(args.frequency, 10, "Frequency should be equal to 10");

}

Test(args_options_freq_tests, no_freq)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--no-frequency"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_frequency_option(&parser, &args), false,
        "args_parse_frequency_option should return false"
    );
    cr_assert_eq(args.frequency, ARGS_DEFAULT_FREQ, "Frequency should be equal to default frequency");
}

Test(args_options_freq_tests, no_freq_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--frequency"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_frequency_option(&parser, &args), true,
        "args_parse_frequency_option should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.frequency, ARGS_DEFAULT_FREQ, "Frequency should be equal to default frequency");
    cr_assert_stderr_eq_str("Missing value for frequency\n");
}

Test(args_options_freq_tests, invalid_freq_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--frequency", "invalid"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_frequency_option(&parser, &args), true,
        "args_parse_frequency_option should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_neq(args.frequency, ARGS_DEFAULT_FREQ, "Frequency should be different of default value");
    cr_assert_stderr_eq_str("Invalid frequency\n");
}

Test(args_options_freq_tests, freq_value_out_of_range, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--frequency", "-10"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_frequency_option(&parser, &args), true,
        "args_parse_frequency_option should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_neq(args.frequency, ARGS_DEFAULT_FREQ, "Frequency should be different of default value");
    cr_assert_stderr_eq_str("Frequency value must be in range [0, 10000]\n");
}

Test(args_options_freq_tests, freq_value_out_of_range_2, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--frequency", "10001"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_frequency_option(&parser, &args), true,
        "args_parse_frequency_option should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.frequency, 10001, "Frequency value v be equal to 10001");
    cr_assert_stderr_eq_str("Frequency value must be in range [0, 10000]\n");
}
