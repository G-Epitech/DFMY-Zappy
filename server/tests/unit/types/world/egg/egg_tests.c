/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/world/egg.h"
#include "types/world/team.h"

Test(egg_new_tests, simple_new)
{
    vector2u_t position = { 10, 5 };
    team_t *team = team_new("Team1", 1);
    egg_t *egg = egg_new(team, position);

    cr_assert_eq(egg->team, team);
    cr_assert_eq(egg->position.x, 10);
    cr_assert_eq(egg->position.y, 5);
    cr_assert_eq(egg->id, 0);
    egg_free(egg);
    team_free(team);
}

Test(egg_new_tests, new_egg_with_malloc_fail)
{
    vector2u_t position = { 10, 5 };

    clcc_return_now(calloc, NULL);
    cr_assert_null(egg_new(NULL, position));
    clcc_disable_control(calloc);
}

Test(egg_free_tests, simple_free)
{
    vector2u_t position = { 10, 5 };
    team_t *team = team_new("Team1", 1);
    egg_t *egg = egg_new(team, position);

    egg_free_as_node_data(egg);
    team_free(team);
}
