/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** test.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "foo.h"

Test(nothing, nothing)
{
    cr_assert_eq(foo(5, 3), 8);
}
