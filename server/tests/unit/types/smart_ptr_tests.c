/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** smart_ptr_tests.c
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/smart_ptr.h"

Test(smart_ptr, new_smart_ptr)
{
    smart_ptr_t *smart_ptr = smart_ptr_new(NULL);

    cr_assert_not_null(smart_ptr);
    cr_assert_eq(smart_ptr->destructor, &free);
    cr_assert_null(smart_ptr->ptr);
    cr_assert_eq(smart_ptr->ref_count, 1);
    smart_ptr_free(smart_ptr);
}

Test(smart_ptr, new_smart_ptr_fail_calloc)
{
    smart_ptr_t *smart_ptr = NULL;

    clcc_return_now(calloc, NULL);
    smart_ptr = smart_ptr_new(NULL);
    cr_assert_null(smart_ptr);
    clcc_disable_control(calloc);
}

Test(smart_ptr, smart_ptr_reference)
{
    smart_ptr_t *smart_ptr = smart_ptr_new(NULL);
    smart_ptr_t *new_ptr = NULL;

    new_ptr = smart_ptr_reference(smart_ptr);
    cr_assert_eq(new_ptr, smart_ptr);
    cr_assert_eq(smart_ptr->ref_count, 2);
    smart_ptr_free(new_ptr);
    cr_assert_eq(smart_ptr->ref_count, 1);
    smart_ptr_free(smart_ptr);
}

Test(smart_ptr, smart_ptr_reference_null_smart_ptr)
{
    cr_assert_null(smart_ptr_reference(NULL));
}

Test(smart_ptr, smart_ptr_free)
{
    smart_ptr_t *smart_ptr = NULL;

    smart_ptr_free(NULL);
    smart_ptr_free(smart_ptr);
}

Test(smart_ptr, smart_ptr_dereference_with_destructor)
{
    char *buffer = strdup("Hello World");
    smart_ptr_t *smart_ptr = smart_ptr_new(buffer);

    smart_ptr->destructor = &free;
    smart_ptr_free(smart_ptr);
}
