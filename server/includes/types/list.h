/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** list
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

// Represent linked list
typedef struct s_list {
    node_t *first;  //First node of list
    node_t *last;   //Last node of list
    size_t len;     //Length of list
} list_t;

// Predicate a condition to check on a node
typedef bool (*list_predicate_t)(node_data_t data);

/**
 * @brief Initialize given list
 * @param list List to initialize
 * @return Created list
 */
void list_init(list_t *list);

/**
 * @brief Create a new list
 * @return Created list
 */
list_t *list_new(void);

/**
 * @brief Free given list and all its nodes with given freer if specified.
 * @param list List to free
 * @param freer freer to call on each node
 */
void list_free(list_t *list, node_freer_t freer);

/**
 * @brief Free given list and all its nodes with given freer if specified.
 * @param list List to free
 * @param freer freer to call on each node
 */
void list_clear(list_t *list, node_freer_t freer);

/**
 * @brief Append given node in given list.
 * @param list List in which append node
 * @param node Node to append in list
 */
void list_append(list_t *list, node_t *node);

/**
 * @brief Push given data in given list.
 * @param list List in which push data
 * @param data Data to push in list
 * @return Push success status
 */
bool list_push(list_t *list, node_data_t data);

/**
 * @brief Remove given node of given list but not free node
 * @param list List in which remove node
 * @param node Node to remove of list
 */
void list_pop(list_t *list, node_t *node);

/**
 * @brief Remove given node of given list and free it.
 * @param list List in which remove node
 * @param node Node to remove of list
 * @param freer Freer to call to free node data
 */
void list_erase(list_t *list, node_t *node, node_freer_t freer);

/**
 * @brief Find node with given data in given list.
 * @param list List in which find node
 * @param data Data to find in list
 * @return Found node or NULL if not found
 */
node_t *list_find(list_t *list, node_data_t data);

/**
 * @brief Look for a node in list with given predicate
 * @param list List in which search node
 * @param predicate Predicate to use to search node
 * @return Predicate success status
 */
bool list_some(list_t *list, list_predicate_t predicate);

/**
 * @brief Merge src list into dest list
 * @param dest List to merge into
 * @param src List to merge
 * @return Merge success status
 */
void list_merge(list_t *dest, list_t *src);
