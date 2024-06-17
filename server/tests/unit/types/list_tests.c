/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** list_tests.c
*/

#include <criterion/criterion.h>
#include "clcc/modules/stdlib.h"
#include "types/list.h"

static void free_ptr_from_node_data(node_data_t data)
{
    free(data.ptr);
}

static bool predicate_null(node_data_t data)
{
    return data.ptr == NULL;
}

Test(types_list, init_list)
{
    list_t list;

    list_init(&list);
    cr_assert(list.first == NULL);
    cr_assert(list.last == NULL);
    cr_assert(list.len == 0);
}

Test(types_list, append_one_item)
{
    list_t list;
    char *str = "HELLO";
    node_t *node = node_new(NODE_DATA_FROM_PTR(str));

    list_init(&list);
    list_append(&list, node);
    cr_assert(list.len == 1);
    cr_assert(NODE_TO_PTR(list.first, char *) == str);
    list_clear(&list, NULL);
}

Test(types_list, append_null_item)
{
    char *str = "HELLO";
    node_t *node = node_new(NODE_DATA_FROM_PTR(str));

    list_append(NULL, node);
}

Test(types_list, append_to_null_list)
{
    list_t list;

    list_init(&list);
    list_append(&list, NULL);
    cr_assert(list.len == 0);
    list_clear(&list, NULL);
}

Test(types_list, append_several_items)
{
    list_t list;
    char *strings[5] = {"Super", "Super2", "Hello", "World", "Foo"};
    node_t *node = NULL;
    size_t j = 0;

    list_init(&list);
    for (size_t i = 0; i < 5; i++) {
        node = node_new(NODE_DATA_FROM_PTR(strings[i]));
        list_append(&list, node);
    }
    node = list.first;
    while (node) {
        cr_assert(NODE_TO_PTR(node, char *) == strings[j++]);
        node = node->next;
    }
    cr_assert(list.len == 5);
    list_clear(&list, NULL);
}

Test(types_list, delete_several_items)
{
    list_t list;
    char *strings[5] = {"Super", "Super2", "Hello", "World", "Foo"};
    node_t *node = NULL;
    node_t *next = NULL;

    list_init(&list);
    for (size_t i = 0; i < 5; i++) {
        node = node_new(NODE_DATA_FROM_PTR(strings[i]));
        list_append(&list, node);
    }
    cr_assert(list.len == 5);
    node = list.first;
    while (node) {
        next = node->next;
        list_erase(&list, node, NULL);
        node = next;
    }
    cr_assert(list.len == 0);
    list_clear(&list, NULL);
}

Test(types_list, remove_several_items)
{
    list_t list;
    char *strings[5] = {"Super", "Super2", "Hello", "World", "Foo"};
    node_t *node = NULL;
    node_t *next = NULL;

    list_init(&list);
    for (size_t i = 0; i < 5; i++) {
        node = node_new(NODE_DATA_FROM_PTR(strings[i]));
        list_append(&list, node);
    }
    cr_assert(list.len == 5);
    node = list.first;
    while (node) {
        next = node->next;
        list_pop(&list, node);
        node = next;
    }
    cr_assert(list.len == 0);
    list_clear(&list, NULL);
}

Test(types_list, delete_several_items_with_freer)
{
    list_t list;
    char *tmp = NULL;
    node_t *node = NULL;
    node_t *next = NULL;

    list_init(&list);
    for (size_t i = 0; i < 12; i++) {
        tmp = strdup("test");
        node = node_new(NODE_DATA_FROM_PTR(tmp));
        list_append(&list, node);
    }
    cr_assert(list.len == 12);
    node = list.first;
    while (node) {
        next = node->next;
        list_erase(&list, node, &free_ptr_from_node_data);
        node = next;
    }
    cr_assert(list.len == 0);
    list_clear(&list, NULL);
}

Test(types_list, free_null_list)
{
    list_clear(NULL, NULL);
}

Test(types_list, remove_last_node_list)
{
    list_t list;
    char *str = "HELLO";
    node_t *node = node_new(NODE_DATA_FROM_PTR(str));
    node_t *node2 = node_new(NODE_DATA_FROM_PTR(str));

    list_append(&list, node);
    list_append(&list, node2);
    list_pop(&list, node2);
    list_clear(&list, NULL);
}

Test(types_list, list_push_simple)
{
    list_t list;
    char *str = "HELLO";

    list_init(&list);
    list_push(&list, NODE_DATA_FROM_PTR(str));
    cr_assert(list.len == 1);
    cr_assert(NODE_TO_PTR(list.first, char *) == str);
    list_clear(&list, NULL);
}

Test(types_list, list_push_null_list)
{
    char *str = "HELLO";

    list_push(NULL, NODE_DATA_FROM_PTR(str));
}

Test(types_list, list_push_new_node_fail)
{
    list_t list;
    char *str = "HELLO";

    clcc_return_now(malloc, NULL);
    list_init(&list);
    list_push(&list, NODE_DATA_FROM_PTR(str));
    cr_assert(list.len == 0);
    list_clear(&list, NULL);
    clcc_disable_control(malloc);
}

Test(types_list, new_list)
{
    list_t *list = list_new();

    cr_assert(list != NULL);
    list_free(list, NULL);
}

Test(types_list, new_list_with_malloc_fail)
{
    clcc_return_now(malloc, NULL);
    cr_assert_null(list_new());
    clcc_disable_control(malloc);
}

Test(types_list, free_list)
{
    list_free(NULL, NULL);
}

Test(types_list, clear_list)
{
    list_t list;
    char *str = "HELLO";

    list_init(&list);
    cr_assert_eq(list.len, 0);
    list_push(&list, NODE_DATA_FROM_PTR(str));
    cr_assert_eq(list.len, 1);
    list_clear(&list, NULL);
    cr_assert_eq(list.len, 0);
}

Test(types_list, find_list)
{
    list_t list;
    char *str = "HELLO";
    char *str2 = "UNKNOWN";
    node_t *node = NULL;

    list_init(&list);
    list_push(&list, NODE_DATA_FROM_PTR("WORLD"));
    list_push(&list, NODE_DATA_FROM_PTR(str));
    node = list_find(&list, NODE_DATA_FROM_PTR(str));
    cr_assert_not_null(node);
    node = list_find(&list, NODE_DATA_FROM_PTR(str2));
    cr_assert_null(node);
    list_clear(&list, NULL);
}


Test(types_list, some_return_result)
{
    list_t *list = list_new();
    char *str = "HELLO";

    list_init(list);
    list_push(list, NODE_DATA_FROM_PTR(str));
    list_push(list, NODE_DATA_FROM_PTR(str));
    list_push(list, NODE_DATA_FROM_PTR(str));
    list_push(list, NODE_DATA_FROM_PTR(NULL));
    list_push(list, NODE_DATA_FROM_PTR(str));

    cr_assert(list_some(list, &predicate_null));
    list_clear(list, NULL);
}

Test(types_list, some_return_no_result)
{
    list_t *list = list_new();
    char *str = "HELLO";

    list_init(list);
    list_push(list, NODE_DATA_FROM_PTR(str));
    list_push(list, NODE_DATA_FROM_PTR(str));
    list_push(list, NODE_DATA_FROM_PTR(str));
    list_push(list, NODE_DATA_FROM_PTR(str));

    cr_assert_not(list_some(list, &predicate_null));
    list_clear(list, NULL);
}

Test(types_list, some_on_null_list)
{
    cr_assert_not(list_some(NULL, &predicate_null));
}

Test(types_list, some_on_empty_list)
{
    list_t *list = list_new();

    list_init(list);
    cr_assert_not(list_some(list, &predicate_null));
    list_clear(list, NULL);
}
