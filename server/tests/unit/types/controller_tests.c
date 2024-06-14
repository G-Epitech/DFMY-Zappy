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
#include "types/controller.h"

Test(controller_tests, init_controller)
{
    controller_t controller = { 0 };

    controller_init(&controller, 12);
    cr_assert_eq(controller.generic.type, CTRL_UNKNOWN);
    cr_assert_eq(controller.generic.socket, 12);
    cr_assert_null(controller.generic.requests);
    cr_assert_null(controller.generic.emissions);
}

Test(controller_tests, new_controller)
{
    controller_t *controller = controller_new(0);

    cr_assert_not_null(controller);
    cr_assert_eq(controller->generic.type, CTRL_UNKNOWN);
    cr_assert_eq(controller->generic.socket, 0);
    cr_assert_not_null(controller->generic.requests);
    cr_assert_not_null(controller->generic.emissions);
    controller_free(controller);
}

Test(controller_tests, new_controller_with_calloc_fail)
{
    clcc_return_now(calloc, NULL);
    cr_assert_null(controller_new(0));
    clcc_disable_control(calloc);
}

Test(controller_tests, new_controller_with_requests_alloc_fail)
{
    clcc_enable_control(malloc);
    clcc_return_value_after(malloc, NULL, 0);
    cr_assert_null(controller_new(0));
    clcc_disable_control(malloc);
}

Test(controller_tests, new_controller_with_emissions_alloc_fail)
{
    clcc_enable_control(malloc);
    clcc_return_value_after(malloc, NULL, 1);
    cr_assert_null(controller_new(0));
    clcc_disable_control(malloc);
}

Test(controller_tests, free_controller)
{
    controller_free(NULL);
}

Test(controller_tests, free_list_of_controllers)
{
    list_t list;
    controller_t *controller1 = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);

    list_init(&list);
    cr_assert_eq(list.len, 0);
    list_push(&list, NODE_DATA_FROM_PTR(controller1));
    list_push(&list, NODE_DATA_FROM_PTR(controller2));
    list_push(&list, NODE_DATA_FROM_PTR(controller3));
    cr_assert_eq(list.len, 3);
    list_clear(&list, &controller_free_as_node_data);
    cr_assert_eq(list.len, 0);
}

Test(controller_tests, controller_read_2_tokens_with_2_newlines)
{
    char buffer[] = "token1\ntoken2\n";
    size_t size = sizeof(buffer) - 1;
    request_token_t token = { 0 };

    cr_assert_eq(controller_read_next_token(buffer, size, &token), false);
    cr_assert_eq(token.size, 7);
    cr_assert_eq(memcmp(token.content, "token1\n", 7), 0);
    cr_assert_eq(controller_read_next_token(buffer + 7, size - 7, &token), true);
    cr_assert_eq(token.size, 7);
    cr_assert_eq(memcmp(token.content, "token2\n", 7), 0);
}

Test(controller_tests, controller_read_2_tokens_with_1_newline)
{
    char buffer[] = "token1\ntoken2";
    size_t size = sizeof(buffer) - 1;
    request_token_t token = { 0 };

    cr_assert_eq(controller_read_next_token(buffer, size, &token), false);
    cr_assert_eq(token.size, 7);
    cr_assert_eq(memcmp(token.content, "token1\n", 7), 0);
    cr_assert_eq(controller_read_next_token(buffer + 7, size - 7, &token), true);
    cr_assert_eq(token.size, 6);
    cr_assert_eq(memcmp(token.content, "token2", 6), 0);
}

Test(controller_tests, get_next_pending_request_with_no_request)
{
    controller_t *controller = controller_new(0);
    request_t *req = controller_get_next_pending_request(controller);

    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(controller->generic.requests->len, 1);
}

Test(controller_tests, get_next_pending_request_with_no_request_but_create_fail_due_to_list_push, .init = cr_redirect_stderr) {
    controller_t *controller = controller_new(0);
    request_t *req = NULL;

    clcc_enable_control(malloc);
    clcc_return_value_after(malloc, NULL, 0);
    controller_get_next_pending_request(controller);
    clcc_disable_control(malloc);
    cr_assert_eq(controller->generic.requests->len, 0);
    cr_assert_null(req);

    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_with_no_request_but_create_fail_due_to_calloc, .init = cr_redirect_stderr) {
    controller_t *controller = controller_new(0);
    request_t *req = NULL;

    clcc_enable_control(calloc);
    clcc_return_value_after(calloc, NULL, 0);
    controller_get_next_pending_request(controller);
    clcc_disable_control(calloc);
    cr_assert_null(req);
    cr_assert_eq(controller->generic.requests->len, 0);

    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_with_request_pending)
{
    controller_t *controller = controller_new(0);
    request_t *req = controller_get_next_pending_request(controller);

    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(controller_get_next_pending_request(controller), req);
    cr_assert_eq(controller->generic.requests->len, 1);

    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_with_request_ready)
{
    controller_t *controller = controller_new(0);
    request_t *req1 = controller_get_next_pending_request(controller);
    request_t *req2 = NULL;

    cr_assert_eq(controller->generic.requests->len, 1);
    cr_assert_not_null(req1);
    cr_assert_eq(req1->status, REQ_PENDING);
    req1->status = REQ_READY;
    req2 = controller_get_next_pending_request(controller);
    cr_assert_not_null(req2);
    cr_assert_eq(req2->status, REQ_PENDING);
    cr_assert_neq(req1, req2);
    cr_assert_eq(controller->generic.requests->len, 2);
    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_on_player_controller)
{
    controller_t *controller = controller_new(0);
    controller->generic.type = CTRL_PLAYER;
    request_t *req = controller_get_next_pending_request(controller);

    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(controller->generic.requests->len, 1);

    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_on_player_controller_with_max_requests, .init = cr_redirect_stdout)
{
    controller_t *controller = controller_new(0);
    controller->generic.type = CTRL_PLAYER;

    cr_assert_eq(controller->generic.requests->len, 0);
    for (int i = 0; i < CTRL_PLAYER_MAX_REQ; ++i) {
        request_t *req = controller_get_next_pending_request(controller);
        req->status = REQ_READY;
    }
    cr_assert_eq(controller->generic.requests->len, CTRL_PLAYER_MAX_REQ);

    request_t *req = controller_get_next_pending_request(controller);
    cr_assert_null(req);

    cr_assert_eq(controller->generic.requests->len, CTRL_PLAYER_MAX_REQ);
    controller_free(controller);
}

Test(controller_tests, get_next_pending_request_on_graphic_controller)
{
    controller_t *controller = controller_new(0);
    controller->generic.type = CTRL_GRAPHIC;
    request_t *req = controller_get_next_pending_request(controller);

    cr_assert_not_null(req);
    cr_assert_eq(req->status, REQ_PENDING);
    cr_assert_eq(controller->generic.requests->len, 1);

    controller_free(controller);
}
