/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** emission.h
*/

#pragma once

#include "types/list.h"
#include "types/smart_ptr.h"

// @brief Specify that the emission is complete and
// end char should be sent
#define EMISSION_COMPLETE 0

// @brief Specify that the emission is partial and
// end char should not be sent
#define EMISSION_PARTIAL 1

// @brief Represent response or an event to send to a single client
typedef struct emission_s {
    // @brief Smart pointer to buffer
    smart_ptr_t *buffer_ptr;
    // @brief Buffer size
    size_t buffer_size;
    // @brief Written bytes
    ssize_t written;
    // @brief Flags
    int flags;
} emission_t;


// @brief Controller emission parameters
typedef struct emission_params_s {
    // @brief Buffer to send
    char *buffer;
    // @brief Buffer size
    size_t buffer_size;
    // @brief Flags
    int flags;
} emission_params_t;

/**
 * @brief Create a new emission
 * @param buffer Buffer for emission content.
 * @param buffer_size Buffer size
 * @param flags Flags for the emission
 * @return Created emission or NULL if failed
 * @warning The ownership of buffer will be transferred to the emission.
 */
emission_t *emission_new(smart_ptr_t *buffer_ptr, size_t buffer_size,
    int flags);

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

/**
 * @brief Create emission parameters from format
 * @param params Emission parameters
 * @param flags Flags for the emission
 * @param format Format string
 * @return true if success, false otherwise
 * @warning Parameters buffer will be allocated and should be freed
 */
bool emission_params_from_format(emission_params_t *params, int flags,
    const char *format, ...) __attribute__((format(printf, 3, 4)));
