/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/trantor/egg.h"
#include "types/trantor/team.h"

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

Test(egg_free_tests, free_list_of_eggs)
{
    vector2u_t position = { 10, 5 };
    team_t *team = team_new("Team1", 1);
    egg_t *egg = NULL;
    list_t *eggs = list_new();

    cr_assert_eq(eggs->len, 0);
    for (int i = 0; i < 10; i++) {
        egg = egg_new(team, position);
        list_push(eggs, NODE_DATA_FROM_PTR(egg));
        cr_assert_eq(eggs->len, i + 1);
    }
    cr_assert_eq(eggs->len, 10);
    list_clear(eggs, &egg_free_as_node_data);
    cr_assert_eq(eggs->len, 0);
    list_free(eggs, NULL);
    team_free(team);
}
