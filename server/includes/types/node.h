/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** node
*/

#pragma once

#define NODE_DATA_FROM_PTR(ptr) ((node_data_t) (void *) ptr)
#define NODE_DATA_TO_PTR(data, ptrtype) ((ptrtype) data.ptr)
#define NODE_TO_PTR(node, ptrtype) ((ptrtype) node->data.ptr)

// Represent a node of linked list
typedef struct s_node node_t;

// Represent data of node_t
typedef union u_node_data {
    void *ptr;          //Any pointer
} node_data_t;

// Represent a node of linked list
typedef struct s_node {
    node_t *prev;       //Previous node
    node_data_t data;   //Data of node
    node_t *next;       //Next node
} node_t;

// Node freer function prototype
typedef void (*node_freer_t)(node_data_t data);

/**
 * @brief Create a new with given data.
 * @param data Data to set to node
 * @return Created node
 */
node_t *node_new(node_data_t data);

/**
 * @brief Free given node and free data of it with freer if specified.
 * @param node Node to free
 * @param freer freer function for node data
 */
void node_free(node_t *node, node_freer_t freer);

/**
 * @brief Unlink given node from its neighbours.
 * @param node Node to unlink
 */
void node_unlink(node_t *node);
