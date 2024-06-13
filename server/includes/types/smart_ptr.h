/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** smart_ptr.h
*/

#pragma once

#include <stdlib.h>

// @brief Smart pointer structure
typedef struct smart_ptr_s {
    // @brief Pointer to the data
    void *ptr;
    // @brief Destructor function
    void (*destructor)(void *);
    // @brief Reference count
    size_t *ref_count;
} smart_ptr_t;

/**
 * @brief Create a new smart pointer
 * @param data Data to store in the smart pointer
 * @return smart_ptr_t* A pointer to the smart pointer
 */
smart_ptr_t *smart_ptr_new(void *data);

/**
 * @brief Reference a smart pointer
 * @param smart_ptr Pointer to the smart pointer
 */
void smart_ptr_reference(smart_ptr_t **new_ptr, smart_ptr_t **smart_ptr);

/**
 * @brief Dereference a smart pointer
 * @param smart_ptr Pointer to the smart pointer
 */
void smart_ptr_dereference(smart_ptr_t **smart_ptr);
