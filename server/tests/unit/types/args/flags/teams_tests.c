/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** map_size.c
*/

#include "types/args.h"
#include "clcc/modules/stdlib.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(args_teams_flags, short_flag)
{
    args_t args;
    char *argv[] = {"./zappy_server", "-n", "team1", "team2" };
    args_parser_t parser = {4, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_teams(&parser, &args), true,
        "args_parse_teams should return true"
    );
    cr_assert_not_null(args.teams, "Teams should not be null");
    cr_assert_str_eq(args.teams[0], "team1", "First team should be team1");
    cr_assert_str_eq(args.teams[1], "team2", "Second team should be team2");
    args_free(&args);
}

Test(args_teams_flags, long_flag)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--teams", "team1", "team2" };
    args_parser_t parser = {4, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_teams(&parser, &args), true,
        "args_parse_teams should return true"
    );
    cr_assert_not_null(args.teams, "Teams should not be null");
    cr_assert_str_eq(args.teams[0], "team1", "First team should be team1");
    cr_assert_str_eq(args.teams[1], "team2", "Second team should be team2");
    args_free(&args);
}

Test(args_teams_flags, missing_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--teams"};
    args_parser_t parser = {2, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_teams(&parser, &args), true,
        "args_parse_teams should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Missing teams names\n");
}

Test(args_teams_flags, already_parsed_value, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--teams", "team1", "team2", "--teams", "team3"};
    args_parser_t parser = {6, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_teams(&parser, &args), true,
        "args_parse_teams should return true"
    );
    cr_assert_eq(parser.error, false, "parser.error should be false");
    parser.current += 1;
    cr_assert_eq(args_parse_teams(&parser, &args), true,
        "args_parse_teams should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Teams names already set\n");
    args_free(&args);
}

Test(args_teams_flags, not_teams_flags)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--custom", "12"};
    args_parser_t parser = {3, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_teams(&parser, &args), false,
        "args_parse_teams should return false"
    );
}

Test(args_teams_flags, empty_team_name, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--teams", "team1",""};
    args_parser_t parser = {4, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_teams(&parser, &args), true,
        "args_parse_teams should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Teams names must not be empty\n");
}

Test(args_teams_flags, duplicated_team_name, .init = cr_redirect_stderr)
{
    args_t args;
    char *argv[] = {"./zappy_server", "--teams", "team1","team2", "team3", "team1"};
    args_parser_t parser = {6, argv, 1, false};

    args_init(&args);
    cr_assert_eq(args_parse_teams(&parser, &args), true,
        "args_parse_teams should return true"
    );
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Duplicated team name 'team1'\n");
}

Test(args_teams_flags, calloc_fail, .init = cr_redirect_stderr) {
    args_t args;
    char *argv[] = {"./zappy_server", "--teams", "team1", "team2"};
    args_parser_t parser = {4, argv, 1, false};

    args_init(&args);
    clcc_return_now(calloc, NULL);
    cr_assert_eq(args_parse_teams(&parser, &args), true,
        "args_parse_teams should return true"
    );
    clcc_disable_control(calloc);
    cr_assert_eq(parser.error, true, "parser.error should be true");
    cr_assert_stderr_eq_str("Failed to allocate memory for teams names\n");
}
