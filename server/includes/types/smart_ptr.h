/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** smart_ptr.h
*/

#pragma once

#include <stdlib.h>

#define SMART_PTR_CAST(type, smart_ptr) ((type)(smart_ptr)->target)

// @brief Smart pointer structure
typedef struct smart_ptr_s {
    // @brief Pointer to the data
    void *target;
    // @brief Destructor function
    void (*destructor)(void *);
    // @brief Reference count
    size_t ref_count;
} smart_ptr_t;

/**
 * @brief Create a new smart pointer
 * @param data Data to store in the smart pointer
 * @return A pointer to the smart pointer or NULL if an error occured
 */
smart_ptr_t *smart_ptr_new(void *data);

/**
 * @brief Reference a smart pointer
 * @param smart_ptr Pointer to the smart pointer
 * @return Given pointer with updated references counter
 */
smart_ptr_t *smart_ptr_reference(smart_ptr_t *ptr);

/**
 * @brief Dereference and free if needed a smart pointer
 * @param smart_ptr Pointer to the smart pointer
 */
void smart_ptr_free(smart_ptr_t *smart_ptr);
