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
