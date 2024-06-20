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
    egg_t *egg = egg_new(-1, 0);

    cr_assert_eq(egg->team, NULL);
    cr_assert_eq(egg->position.x, 0);
    cr_assert_eq(egg->position.y, 0);
    cr_assert_eq(egg->id, 0);
    cr_assert_eq(egg->laid_by, -1);
    egg_free(egg);
}

Test(egg_new_tests, new_egg_with_malloc_fail)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(egg_new(0, 0));
    clcc_disable_control(calloc);
}

Test(egg_free_tests, free_list_of_eggs)
{
    egg_t *egg = NULL;
    list_t *eggs = list_new();

    cr_assert_eq(eggs->len, 0);
    for (int i = 0; i < 10; i++) {
        egg = egg_new(-1, i);
        list_push(eggs, NODE_DATA_FROM_PTR(egg));
        cr_assert_eq(eggs->len, i + 1);
        cr_assert_eq(egg->laid_by, -1);
        cr_assert_eq(egg->id, i);
    }
    cr_assert_eq(eggs->len, 10);
    list_clear(eggs, &egg_free_as_node_data);
    cr_assert_eq(eggs->len, 0);
    list_free(eggs, NULL);
}
