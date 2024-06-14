/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** emission.h
*/

#pragma once

#include "types/list.h"

// @brief Buffer writing section size for emission
#define EMISSION_BUFF_SIZE 4096

// @brief Represent response or an event to send to a single client
typedef struct emission_s {
    // @brief Buffer for emission content
    char *buffer;
    // @brief Buffer size
    size_t buffer_size;
} emission_t;

/**
 * @brief Create a new emission
 * @param buffer Buffer for emission content.
 * @param buffer_size Buffer size
 * @return Created emission or NULL if failed
 * @warning The ownership of buffer will be transferred to the emission.
 */
emission_t *emission_new(char *buffer, size_t buffer_size);

/**
 * @brief Free given emission
 * @param emission Emission to free
 */
void emission_free(emission_t *emission);

/**
 * @brief Free given emission as node data
 * @param data Data to free as node data
 */
void emission_free_as_node_data(node_data_t data);
