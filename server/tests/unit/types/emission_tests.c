/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** emission_tests.c
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/emission.h"

Test(emission_tests, new_emission)
{
    char *buffer = strdup("Hello World");
    emission_t *emission = emission_new(buffer, 11);

    cr_assert_not_null(emission);
    cr_assert_str_eq(emission->buffer, "Hello World");
    cr_assert_eq(emission->buffer_size, 11);
    emission_free(emission);
}

Test(emission_tests, new_emission_with_malloc_fail)
{
    char *buffer = strdup("Hello World");

    clcc_return_now(calloc, NULL);
    cr_assert_null(emission_new(buffer, 11));
    clcc_disable_control(calloc);
}

Test(emission_tests, free_null_emission)
{
    emission_free(NULL);
}

Test(emission_tests, free_emission_as_node_data)
{
    emission_t *emission = NULL;
    char *buffer = NULL;
    list_t *emissions = list_new();

    cr_assert_eq(emissions->len, 0);
    for (int i = 0; i < 10; i++) {
        buffer = strdup("Hello");
        emission = emission_new(buffer, 6);
        list_push(emissions, NODE_DATA_FROM_PTR(emission));
        cr_assert_eq(emissions->len, i + 1);
    }
    cr_assert_eq(emissions->len, 10);
    list_clear(emissions, &emission_free_as_node_data);
    cr_assert_eq(emissions->len, 0);
    list_free(emissions, NULL);
}
