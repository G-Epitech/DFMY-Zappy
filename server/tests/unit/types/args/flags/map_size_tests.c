/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "types/args.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(args_map_size_flags_tests, short_width)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-x", "15"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(args.width, 15, "Map width should be equal to 10");
}

Test(args_map_size_flags_tests, long_width)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--width", "15"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(args.width, 15, "Map width should be equal to 10");
}

Test(args_map_size_flags_tests, short_height)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-y", "15"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(args.height, 15, "Map height should be equal to 10");
}

Test(args_map_size_flags_tests, long_height)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--height", "15"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(args.height, 15, "Map height should be equal to 10");
}

Test(args_map_size_flags_tests, too_little_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--height", "1"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.height, 1, "Map height should be equal to 1");
    cr_assert_stderr_eq_str("Value of map height must be in range [10, 40]\n");
}

Test(args_map_size_flags_tests, too_big_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--width", "1000"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_eq(args.width, 1000, "Map height should be equal to 1000");
    cr_assert_stderr_eq_str("Value of map width must be in range [10, 40]\n");
}

Test(args_map_size_flags_tests, invalid_number, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--height", "invalid"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Invalid map height value\n");
}

Test(args_map_size_flags_tests, missing_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--height"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Missing value for map height\n");
}

Test(args_map_size_flags_tests, already_parsed_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--width", "12", "--width", "17"};
    args_parser_t parser = {5, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(parser.error, false, "parser.error should be false");
    parser.current += 1;
    cr_assert_eq(args_parse_map_size(&parser, &args), true,
        "args_parse_map_size should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Map width already set\n");
}

Test(args_map_size_flags_tests, neither_width_or_height)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--custom", "12"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_map_size(&parser, &args), false,
        "args_parse_map_size should return false"
    );
}

