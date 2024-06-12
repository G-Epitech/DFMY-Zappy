/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** shared_event_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "clcc/modules/stdlib.h"
#include "types/shared_event.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

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

Test(shared_event_tests, free_list_of_events)
{
    shared_event_t *shared_event1 = shared_event_new(strdup("Hello World"), 11);
    shared_event_t *shared_event2 = shared_event_new(strdup("Hello World"), 11);
    list_t *list = list_new();

    list_push(list, NODE_DATA_FROM_PTR(shared_event1));
    list_push(list, NODE_DATA_FROM_PTR(shared_event2));
    cr_assert_eq(list->len, 2);
    list_clear(list, &shared_event_free_as_node_data);
    cr_assert_eq(list->len, 0);
    list_free(list, NULL);
}

Test(shared_event_tests, subscribe_to_shared_event)
{
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller = controller_new(0);

    cr_assert_eq(shared_event->subscribers->len, 0);
    cr_assert_eq(shared_event_subscribe(shared_event, controller), true);
    cr_assert_eq(shared_event->subscribers->len, 1);
    controller_free(controller);
}

Test(shared_event_tests, subscribe_to_shared_event_with_null_shared_event)
{
    controller_t *controller = controller_new(0);

    cr_assert_eq(shared_event_subscribe(NULL, controller), false);
    controller_free(controller);
}

Test(shared_event_tests, subscribe_to_shared_event_with_null_controller)
{
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);

    cr_assert_eq(shared_event_subscribe(shared_event, NULL), false);
    shared_event_free(shared_event);
}

Test(shared_event_tests, subscribe_all_players, .init = redirect_all_std)
{
    list_t *controllers = list_new();
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller1 = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);

    cr_assert_eq(shared_event->subscribers->len, 0);
    controller1->generic.type = CTRL_PLAYER;
    controller2->generic.type = CTRL_PLAYER;
    controller3->generic.type = CTRL_GRAPHIC;
    list_push(controllers, NODE_DATA_FROM_PTR(controller1));
    list_push(controllers, NODE_DATA_FROM_PTR(controller2));
    list_push(controllers, NODE_DATA_FROM_PTR(controller3));
    shared_event_subscribe_players(shared_event, controllers);
    cr_assert_eq(shared_event->subscribers->len, 2);
    shared_event_free(shared_event);
    list_free(controllers, &controller_free_as_node_data);
}

Test(shared_event_tests, subscribe_all_players_fail, .init = redirect_all_std)
{
    list_t *controllers = list_new();
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller1 = controller_new(0);

    controller1->generic.type = CTRL_PLAYER;
    list_push(controllers, NODE_DATA_FROM_PTR(controller1));
    clcc_return_now(malloc, NULL);
    shared_event_subscribe_players(shared_event, controllers);
    clcc_disable_control(malloc);
    cr_assert_eq(shared_event->subscribers->len, 0);
    shared_event_free(shared_event);
    list_free(controllers, &controller_free_as_node_data);
}

Test(shared_event_tests, subscribe_all_grahpics, .init = redirect_all_std)
{
    list_t *controllers = list_new();
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller1 = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);

    cr_assert_eq(shared_event->subscribers->len, 0);
    controller1->generic.type = CTRL_PLAYER;
    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_GRAPHIC;
    list_push(controllers, NODE_DATA_FROM_PTR(controller1));
    list_push(controllers, NODE_DATA_FROM_PTR(controller2));
    list_push(controllers, NODE_DATA_FROM_PTR(controller3));
    shared_event_subscribe_graphics(shared_event, controllers);
    cr_assert_eq(shared_event->subscribers->len, 2);
    shared_event_free(shared_event);
    list_free(controllers, &controller_free_as_node_data);
}

Test(shared_event_tests, subscribe_all_grahpics_fail, .init = redirect_all_std)
{
    list_t *controllers = list_new();
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller1 = controller_new(0);

    cr_assert_eq(shared_event->subscribers->len, 0);
    controller1->generic.type = CTRL_GRAPHIC;
    list_push(controllers, NODE_DATA_FROM_PTR(controller1));
    clcc_return_now(malloc, NULL);
    shared_event_subscribe_graphics(shared_event, controllers);
    clcc_disable_control(malloc);
    cr_assert_eq(shared_event->subscribers->len, 0);
    shared_event_free(shared_event);
    list_free(controllers, &controller_free_as_node_data);
}

Test(shared_event_tests, subscribe_all, .init = redirect_all_std)
{
    list_t *controllers = list_new();
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller1 = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);

    controller1->generic.type = CTRL_PLAYER;
    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_GRAPHIC;
    list_push(controllers, NODE_DATA_FROM_PTR(controller1));
    list_push(controllers, NODE_DATA_FROM_PTR(controller2));
    list_push(controllers, NODE_DATA_FROM_PTR(controller3));
    shared_event_subscribe_all(shared_event, controllers);
    cr_assert_eq(shared_event->subscribers->len, 3);
    shared_event_free(shared_event);
    list_free(controllers, &controller_free_as_node_data);
}

Test(shared_event_tests, subscribe_all_fail, .init = redirect_all_std)
{
    list_t *controllers = list_new();
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller1 = controller_new(0);

    controller1->generic.type = CTRL_PLAYER;
    list_push(controllers, NODE_DATA_FROM_PTR(controller1));
    clcc_return_now(malloc, NULL);
    shared_event_subscribe_all(shared_event, controllers);
    clcc_disable_control(malloc);
    cr_assert_eq(shared_event->subscribers->len, 0);
    shared_event_free(shared_event);
    list_free(controllers, &controller_free_as_node_data);
}

Test(shared_event_tests, unsubscribe)
{
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller1 = controller_new(0);

    shared_event_subscribe(shared_event, controller1);
    cr_assert_eq(shared_event->subscribers->len, 1);
    cr_assert(shared_event_unsubscribe(shared_event, controller1));
    cr_assert_eq(shared_event->subscribers->len, 0);
    shared_event_free(shared_event);
    controller_free(controller1);
}

Test(shared_event_tests, unsubscribe_with_null_shared_event)
{
    controller_t *controller1 = controller_new(0);

    cr_assert_eq(shared_event_unsubscribe(NULL, controller1), false);
    controller_free(controller1);
}

Test(shared_event_tests, unsubscribe_with_null_controller)
{
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);

    cr_assert_eq(shared_event_unsubscribe(shared_event, NULL), false);
    shared_event_free(shared_event);
}

Test(shared_event_tests, unsubscribe_with_no_subscribers)
{
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller1 = controller_new(0);

    cr_assert_eq(shared_event->subscribers->len, 0);
    cr_assert_eq(shared_event_unsubscribe(shared_event, controller1), false);
    shared_event_free(shared_event);
    controller_free(controller1);
}

Test(shared_event_tests, unsubscribe_a_non_subscriber)
{
    shared_event_t *shared_event = shared_event_new(strdup("Hello World"), 11);
    controller_t *controller1 = controller_new(0);
    controller_t *controller2 = controller_new(0);

    shared_event_subscribe(shared_event, controller1);
    shared_event_unsubscribe(shared_event, controller2);
    cr_assert_eq(shared_event->subscribers->len, 1);
    shared_event_free(shared_event);
    controller_free(controller1);
    controller_free(controller2);
}
