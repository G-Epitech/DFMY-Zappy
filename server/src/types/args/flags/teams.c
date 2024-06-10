/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** port.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types/args.h"

static size_t count_teams(args_parser_t *parser)
{
    char *arg = ARGS_PARSER_CURRENT(parser);
    int first_team_index = parser->current;
    size_t teams_len = 0;

    while (parser->current < parser->argc && arg[0] != '-') {
        teams_len += 1;
        parser->current += 1;
        arg = ARGS_PARSER_CURRENT(parser);
    }
    parser->current = first_team_index;
    return teams_len;
}

static bool is_valid_team_name(const char *name, char **teams)
{
    size_t i = 0;

    if (strlen(name) == 0) {
        fprintf(stderr, "Teams names must not be empty\n");
        return false;
    }
    while (teams[i] != NULL) {
        if (strcmp(name, teams[i]) == 0) {
            fprintf(stderr, "Duplicated team name '%s'\n", name);
            return false;
        }
        i += 1;
    }
    return true;
}

static void read_teams_names(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);
    size_t teams_len = count_teams(parser);

    args->teams = calloc(teams_len + 1, sizeof(char *));
    if (args->teams == NULL) {
        fprintf(stderr, "Failed to allocate memory for teams names\n");
        parser->error = true;
        return;
    }
    for (size_t i = 0; i < teams_len; i += 1) {
        if (!is_valid_team_name(arg, args->teams)) {
            parser->error = true;
            return;
        }
        args->teams[i] = arg;
        parser->current += (i + 1) < teams_len ? 1 : 0;
        arg = ARGS_PARSER_CURRENT(parser);
    }
}

bool args_parse_teams(args_parser_t *parser, args_t *args)
{
    char *arg = ARGS_PARSER_CURRENT(parser);

    if (strcmp(arg, "--teams") != 0 && strcmp(arg, "-n") != 0)
        return false;
    if (!args_parser_has_next_arg(parser, "Missing teams names"))
        return true;
    if (args->teams) {
        fprintf(stderr, "Teams names already set\n");
        parser->error = true;
        return true;
    }
    read_teams_names(parser, args);
    return true;
}
