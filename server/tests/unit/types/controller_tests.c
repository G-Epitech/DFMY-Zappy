/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "clcc/modules/stdlib.h"
#include "clcc/modules/unistd.h"
#include "types/list.h"
#include "types/controller.h"
#include "types/emission.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

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

Test(controller_emissions_tests, add_emission_to_controller, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);
    char *buffer = strdup("Hello World");
    smart_ptr_t *buffer_ptr = smart_ptr_new(buffer);

    buffer_ptr->destructor = &free;
    cr_assert_eq(controller->generic.emissions->len, 0);
    controller_add_emission(controller, buffer_ptr, 13);
    cr_assert_eq(controller->generic.emissions->len, 1);
    list_free(controller->generic.emissions, &emission_free_as_node_data);
}

Test(controller_emissions_tests, add_emission_to_controller_with_calloc_fail, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);
    char *buffer = strdup("Hello World");
    smart_ptr_t *buffer_ptr = smart_ptr_new(buffer);

    clcc_return_now(calloc, NULL);
    cr_assert_eq(controller_add_emission(controller, buffer_ptr, 13), false);
    clcc_disable_control(calloc);
    smart_ptr_free(buffer_ptr);
}

Test(controller_emissions_tests, add_emission_to_controller_with_malloc_fail, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);
    smart_ptr_t *buffer_ptr = smart_ptr_new(strdup("Hello World"));

    clcc_return_now(malloc, NULL);
    cr_assert_eq(controller_add_emission(controller, buffer_ptr, 13), false);
    clcc_disable_control(malloc);
    smart_ptr_free(buffer_ptr);
}

Test(controller_emissions_tests, add_emission_with_null_controller, .init = redirect_all_std)
{
    char *buffer = strdup("Hello World");
    smart_ptr_t *buffer_ptr = smart_ptr_new(buffer);

    cr_assert_eq(controller_add_emission(NULL, buffer_ptr, 13), false);
    smart_ptr_free(buffer_ptr);
}

Test(controller_emissions_tests, add_emission_with_null_smart_ptr, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);

    cr_assert_eq(controller_add_emission(controller, NULL, 13), false);
    controller_free(controller);
}

Test(controller_emissions_tests, add_emission_with_null_smart_ptr_data, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);
    smart_ptr_t *buffer_ptr = smart_ptr_new(NULL);

    buffer_ptr->destructor = NULL;
    cr_assert_eq(controller_add_emission(controller, buffer_ptr, 13), false);
    controller_free(controller);
}

Test(controller_emissions_tests, controller_emit, .init = redirect_all_std)
{
    controller_t *controller = controller_new(STDERR_FILENO);
    char *buffer = strdup("Hello World");
    smart_ptr_t *buffer_ptr = smart_ptr_new(buffer);
    FILE* local_stderr = cr_get_redirected_stderr();
    char buffer_stderr[10000];

    controller_add_emission(controller, buffer_ptr, 13);
    memset(buffer_stderr, 0, sizeof(buffer_stderr));
    controller_emit(controller);
    fflush(stderr);
    fflush(local_stderr);
    fread(buffer_stderr, sizeof(char), sizeof(buffer_stderr), local_stderr);
    cr_assert_str_eq(buffer_stderr, "Hello World");
    cr_assert_eq(controller->generic.emissions->len, 0);
    list_free(controller->generic.emissions, &emission_free_as_node_data);
    free(controller);
}

Test(controller_emissions_tests, null_controller)
{
    controller_emit(NULL);
}

Test(controller_emissions_tests, null_emissions, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);

    controller->generic.emissions = NULL;
    controller_emit(controller);
    free(controller);
}

Test(controller_emissions_tests, no_emissions, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);

    controller_emit(controller);
    free(controller);
}

Test(controller_emissions_tests, write_error, .init = redirect_all_std)
{
    controller_t *controller = controller_new(0);
    char *buffer = strdup("Hello World");
    smart_ptr_t *buffer_ptr = smart_ptr_new(buffer);

    controller_add_emission(controller, buffer_ptr, 13);
    clcc_return_now(write, -1);
    controller_emit(controller);
    clcc_disable_control(write);
    free(controller);
}

Test(controller_emissions_tests, add_graphics_shared_emissions, .init = redirect_all_std)
{
    list_t *list = list_new();
    controller_t *controller = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);
    char *buffer = strdup("Hello World");

    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_GRAPHIC;
    controller->generic.type = CTRL_PLAYER;
    list_push(list, NODE_DATA_FROM_PTR(controller));
    list_push(list, NODE_DATA_FROM_PTR(controller2));
    list_push(list, NODE_DATA_FROM_PTR(controller3));
    controller_graphics_list_add_emission(list, buffer, 13);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(controller2->generic.emissions->len, 1);
    cr_assert_eq(controller3->generic.emissions->len, 1);
}

Test(controller_emissions_tests, add_players_shared_emissions, .init = redirect_all_std)
{
    list_t *list = list_new();
    controller_t *controller = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);
    char *buffer = strdup("Hello World");

    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_GRAPHIC;
    controller->generic.type = CTRL_PLAYER;
    list_push(list, NODE_DATA_FROM_PTR(controller));
    list_push(list, NODE_DATA_FROM_PTR(controller2));
    list_push(list, NODE_DATA_FROM_PTR(controller3));
    controller_players_list_add_emission(list, buffer, 13);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(controller2->generic.emissions->len, 1);
    cr_assert_eq(controller3->generic.emissions->len, 1);
}

Test(controller_emissions_tests, add_all_shared_emissions, .init = redirect_all_std)
{
    list_t *list = list_new();
    controller_t *controller = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);
    char *buffer = strdup("Hello World");

    controller->generic.type = CTRL_PLAYER;
    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_UNKNOWN;
    list_push(list, NODE_DATA_FROM_PTR(controller));
    list_push(list, NODE_DATA_FROM_PTR(controller2));
    list_push(list, NODE_DATA_FROM_PTR(controller3));
    controller_all_list_add_emission(list, buffer, 13);
    cr_assert_eq(controller->generic.emissions->len, 1);
    cr_assert_eq(controller2->generic.emissions->len, 1);
    cr_assert_eq(controller3->generic.emissions->len, 0);
}

Test(controller_emissions_tests, add_shared_emissions_with_null_buffer, .init = redirect_all_std)
{
    list_t *list = list_new();

    cr_assert_eq(controller_graphics_list_add_emission(list, NULL, 13), false);
    cr_assert_eq(controller_all_list_add_emission(list, NULL, 13), false);
    cr_assert_eq(controller_players_list_add_emission(list, NULL, 13), false);
    list_free(list, NULL);
}

Test(controller_emissions_tests, add_shared_emissions_with_null_list, .init = redirect_all_std)
{
    char *buffer = strdup("Hello World");

    cr_assert_eq(controller_graphics_list_add_emission(NULL, buffer, 13), false);
    cr_assert_eq(controller_all_list_add_emission(NULL, buffer, 13), false);
    cr_assert_eq(controller_players_list_add_emission(NULL, buffer, 13), false);
    free(buffer);
}

Test(controller_emissions_tests, add_shared_emissions_with_calloc_fail, .init = redirect_all_std)
{
    list_t *list = list_new();
    controller_t *controller = controller_new(0);
    controller_t *controller2 = controller_new(0);
    controller_t *controller3 = controller_new(0);
    char *buffer = strdup("Hello World");

    controller2->generic.type = CTRL_GRAPHIC;
    controller3->generic.type = CTRL_GRAPHIC;
    controller->generic.type = CTRL_PLAYER;
    list_push(list, NODE_DATA_FROM_PTR(controller));
    list_push(list, NODE_DATA_FROM_PTR(controller2));
    list_push(list, NODE_DATA_FROM_PTR(controller3));
    clcc_return_now(calloc, NULL);
    cr_assert_eq(controller_graphics_list_add_emission(list, buffer, 13), false);
    cr_assert_eq(controller_all_list_add_emission(list, buffer, 13), false);
    cr_assert_eq(controller_players_list_add_emission(list, buffer, 13), false);
    clcc_disable_control(calloc);
    cr_assert_eq(controller->generic.emissions->len, 0);
    cr_assert_eq(controller2->generic.emissions->len, 0);
    cr_assert_eq(controller3->generic.emissions->len, 0);
    list_free(list, &controller_free_as_node_data);
}

Test(controller_write_tests, null_controller)
{
    cr_assert_eq(controller_write(NULL, "Hello World", 11), -1);
}

Test(controller_write_tests, null_msg)
{
    controller_t *controller = controller_new(0);

    cr_assert_eq(controller_write(controller, NULL, 11), -1);
    free(controller);
}
