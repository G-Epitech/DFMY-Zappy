/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** shared_event_tests.c
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/shared_event.h"

Test(shared_event_tests, new_shared_event)
{
    char *buffer = strdup("Hello World");
    shared_event_t *shared_event = shared_event_new(buffer, 11);

    cr_assert_not_null(shared_event);
    cr_assert_not_null(shared_event->subscribers);
    cr_assert_eq(shared_event->subscribers->len, 0);
    cr_assert_str_eq(shared_event->buffer, "Hello World");
    cr_assert_eq(shared_event->buffer_size, 11);
    shared_event_free(shared_event);
}

Test(shared_event_tests, new_shared_event_with_malloc_fail)
{
    char *buffer = strdup("Hello World");

    clcc_return_now(calloc, NULL);
    cr_assert_null(shared_event_new(buffer, 11));
    clcc_disable_control(calloc);
}

Test(shared_event_tests, new_shared_event_fail_due_to_list_new)
{
    char *buffer = strdup("Hello World");

    clcc_return_now(malloc, NULL);
    cr_assert_null(shared_event_new(buffer, 11));
    clcc_disable_control(malloc);
}

Test(shared_event_tests, new_shared_event_with_null_buffer_and_size_0)
{
    shared_event_t *shared_event = shared_event_new(NULL, 0);

    cr_assert_not_null(shared_event);
    cr_assert_not_null(shared_event->subscribers);
    cr_assert_eq(shared_event->subscribers->len, 0);
    cr_assert_null(shared_event->buffer);
    cr_assert_eq(shared_event->buffer_size, 0);
    shared_event_free(shared_event);
}

Test(shared_event_tests, free_null_shared_event)
{
    shared_event_free(NULL);
}
