/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/string.h"
#include "clcc/modules/stdlib.h"
#include "types/world/team.h"

Test(team_tests, simple_new)
{
    team_t *team = team_new("Team1", 1);

    cr_assert_str_eq(team->name, "Team1");
    cr_assert_eq(team->players->len, 0);
    cr_assert_eq(team->eggs->len, 0);
    cr_assert_eq(team->min_slots, 1);
    team_free(team);
}

Test(team_tests, new_team_with_team_struct_malloc_fail)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(team_new("Team1", 1));
    clcc_disable_control(calloc);
}

Test(team_tests, new_team_with_players_list_malloc_fail)
{
    clcc_return_value_after(malloc, NULL, 1);
    clcc_enable_control(malloc);
    cr_assert_null(team_new("Team1", 1));
    clcc_disable_control(malloc);
}

Test(team_tests, new_team_with_egg_list_malloc_fail)
{
    clcc_return_value_after(malloc, NULL, 2);
    clcc_enable_control(malloc);
    cr_assert_null(team_new("Team1", 1));
    clcc_disable_control(malloc);
}

/*Test(team_tests, new_team_with_team_name_dup_fail)
{
    clcc_return_now(strdup, NULL);
    cr_assert_null(team_new("Team1", 1));
    clcc_disable_control(strdup);
}*/

Test(team_tests, simple_free)
{
    team_t *team = team_new("Team1", 1);

    team_free(team);
}

Test(team_tests, free_null_team)
{
    team_free(NULL);
}

Test(team_tests, free_list_of_teams)
{
    team_t *team = NULL;
    list_t *teams = list_new();

    cr_assert_eq(teams->len, 0);
    for (int i = 0; i < 10; i++) {
        team = team_new("Team1", 2);
        list_push(teams, NODE_DATA_FROM_PTR(team));
        cr_assert_eq(teams->len, i + 1);
    }
    cr_assert_eq(teams->len, 10);
    list_clear(teams, &team_free_as_node_data);
    cr_assert_eq(teams->len, 0);
    list_free(teams, NULL);
}
