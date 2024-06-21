/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "clcc/modules/stdlib.h"
#include "types/buffer.h"

Test(buffer_new_tests, test_buffer_new)
{
    buffer_t *buffer = buffer_new(10);

    cr_assert_not_null(buffer);
    cr_assert_not_null(buffer->data);
    cr_assert_eq(buffer->size, 10);
    cr_assert_eq(buffer->bytes, 0);

    buffer_free(buffer);
}

Test(buffer_new_tests, buffer_fail_due_to_calloc)
{
    buffer_t *buffer = NULL;

    clcc_return_now(calloc, NULL);
    buffer = buffer_new(10);
    clcc_disable_control(calloc);
    cr_assert_null(buffer);
}

Test(buffer_new_tests, buffer_fail_due_to_data_calloc)
{
    buffer_t *buffer = NULL;

    clcc_return_value_after(calloc, NULL, 1);
    buffer = buffer_new(10);
    clcc_disable_control(calloc);
    cr_assert_null(buffer);
}
