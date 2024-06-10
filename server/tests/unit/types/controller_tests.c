/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/list.h"
#include "types/controller.h"

Test(controller_tests, new_controller)
{
    controller_t *controller = controller_new(0);

    cr_assert_not_null(controller);
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
