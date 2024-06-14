/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "types/args.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(args_options_help_tests, short_help)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-h"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_help_option(&parser, &args), true);
    cr_assert_eq(args.help, true);
}

Test(args_options_help_tests, long_help)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--help"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_help_option(&parser, &args), true);
    cr_assert_eq(args.help, true);
}

Test(args_options_help_tests, no_help)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--no-help"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_not(args_parse_help_option(&parser, &args));
    cr_assert_not(args.help);
}
