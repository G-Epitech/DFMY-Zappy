/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/list.h"
#include "types/request.h"

Test(request_tests, new_request)
{
    request_t *request = request_new();

    cr_assert_not_null(request);
    cr_assert_not_null(request->buffer);
    cr_assert_eq(request->content_size, 0);
    cr_assert_eq(request->status, REQ_PENDING);
    cr_assert_eq(request->buffer_size, REQUEST_BUFF_SIZE);
    request_free(request);
}

Test(request_tests, new_request_with_calloc_fail)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(request_new());
    clcc_disable_control(calloc);
}

Test(request_tests, new_request_with_buffer_calloc_fail)
{
    clcc_enable_control(calloc);
    clcc_return_value_after(calloc, NULL, 1);
    cr_assert_null(request_new());
    clcc_disable_control(calloc);
}

Test(request_tests, free_null_request)
{
    request_free(NULL);
}

Test(request_tests, free_request)
{
    request_t *request = request_new();

    request_free(request);
}

Test(request_tests, free_list_of_requests)
{
    list_t list;
    request_t *request = request_new();

    list_init(&list);
    list_append(&list, node_new(NODE_DATA_FROM_PTR(request)));
    list_clear(&list, &request_free_as_node_data);
    cr_assert_eq(list.len, 0);
}
