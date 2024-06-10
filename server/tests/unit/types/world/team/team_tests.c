/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/world/team.h"

Test(team_new_tests, simple_new)
{
    team_t *team = team_new("Team1", 1);

    cr_assert_str_eq(team->name, "Team1");
    cr_assert_eq(team->players->len, 0);
    cr_assert_eq(team->eggs->len, 0);
    cr_assert_eq(team->min_slots, 1);
    team_free(team);
}

Test(team_new_tests, new_team_with_team_struct_malloc_fail)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(team_new("Team1", 1));
    clcc_disable_control(calloc);
}

Test(team_new_tests, new_team_with_team_list_malloc_fail)
{
    clcc_return_value_after(malloc, NULL, 1);
    clcc_enable_control(malloc);
    cr_assert_null(team_new("Team1", 1));
    clcc_disable_control(malloc);
}

Test(team_free_tests, simple_free)
{
    team_t *team = team_new("Team1", 1);

    team_free(team);
}

Test(team_free_tests, free_as_node_data)
{
    team_t *team = team_new("Team1", 1);

    team_free_as_node_data(team);
}
