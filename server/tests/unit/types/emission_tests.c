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
