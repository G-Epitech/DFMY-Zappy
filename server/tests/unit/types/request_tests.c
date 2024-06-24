/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
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
    cr_assert_eq(request->buffer_size, REQ_BUFF_SIZE);
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

Test(request_tests, append_request_not_greater_than_buff_size)
{
    request_t *request = request_new();
    char data[REQ_BUFF_SIZE - 10] = { 0 };

    memset(data, 'a', sizeof(data));
    cr_assert(request_append(request, data, sizeof(data)));
    cr_assert_eq(request->content_size, sizeof(data));
    cr_assert_str_eq(request->buffer, data);
    request_free(request);
}

Test(request_tests, append_request_greater_than_buff_size)
{
    request_t *request = request_new();
    char data1[REQ_BUFF_SIZE] = { 0 };
    char data2[REQ_BUFF_SIZE - 10] = { 0 };

    memset(data1, 'a', sizeof(data1));
    memset(data2, 'b', sizeof(data2));
    cr_assert(request_append(request, data1, sizeof(data1)));
    cr_assert_eq(request->content_size, sizeof(data1));
    cr_assert(memcmp(request->buffer, data1, sizeof(data1)) == 0);
    cr_assert(request_append(request, data2, sizeof(data2)));
    cr_assert_eq(request->content_size, sizeof(data1) + sizeof(data2));
    cr_assert(memcmp(request->buffer, data1, sizeof(data1)) == 0);
    cr_assert(memcmp(request->buffer + sizeof(data1), data2, sizeof(data2)) == 0);
    request_free(request);
}

Test(request_tests, append_request_realloc_fail, .init = cr_redirect_stderr)
{
    request_t *request = request_new();
    char data1[REQ_BUFF_SIZE];
    char data2[REQ_BUFF_SIZE + 10];

    memset(data1, 'a', sizeof(data1));
    memset(data2, 'b', sizeof(data2));
    cr_assert(request_append(request, data1, sizeof(data1)));
    cr_assert_eq(request->content_size, sizeof(data1));
    clcc_return_now(realloc, NULL);
    cr_assert_not(request_append(request, data2, sizeof(data2)));
    clcc_disable_control(realloc);
    cr_assert_eq(request->content_size, sizeof(data1));
    request_free(request);
}

Test(request_tests, append_request_overflow_limit, .init = cr_redirect_stderr)
{
    request_t *request = request_new();
    char data[REQ_BUFF_SIZE] = { 0 };

    memset(data, 'a', sizeof(data));
    for (int i = 0; i < (REQ_MAX_BUFF_SIZE / REQ_BUFF_SIZE); i++) {
        cr_assert(request_append(request, data, sizeof(data)));
    }
    cr_assert_eq(request->status, REQ_PENDING);
    cr_assert_not(request_append(request, data, sizeof(data)));
    cr_assert_eq(request->content_size, REQ_MAX_BUFF_SIZE);
    cr_assert_eq(request->status, REQ_INVALID);
    request_free(request);
}


Test(request_tests, get_first_token)
{
    request_t *request = request_new();
    request_token_t token = { 0 };
    char data[] = "Hello World";

    cr_assert(request_append(request, data, sizeof(data) - 1));
    cr_assert(request_get_token(request, 0, &token));
    cr_assert(memcmp(token.content, "Hello", 5) == 0);
    cr_assert_eq(token.size, 5);
    request_free(request);
}

Test(request_tests, get_second_token)
{
    request_t *request = request_new();
    request_token_t token = { 0 };
    char data[] = "Hello World";

    cr_assert(request_append(request, data, sizeof(data) - 1));
    cr_assert(request_get_token(request, 1, &token));
    cr_assert_eq(token.size, 5, "Token size is %zu", token.size);
    cr_assert(memcmp(token.content, "World", 5) == 0);
    request_free(request);
}

Test(request_tests, get_token_out_of_bound)
{
    request_t *request = request_new();
    request_token_t token = { 0 };
    char data[] = "Hello World";

    cr_assert(request_append(request, data, sizeof(data) - 1));
    cr_assert_not(request_get_token(request, 12, &token));

    request_free(request);
}

Test(request_tests, get_token_12)
{
    request_t *request = request_new();
    request_token_t token = { 0 };
    char data[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

    cr_assert(request_append(request, data, sizeof(data) - 1));
    cr_assert(request_get_token(request, 12, &token));
    cr_assert_eq(token.size, strlen("incididunt"));
    cr_assert(memcmp(token.content, "incididunt", strlen("incididunt")) == 0);

    request_free(request);
}