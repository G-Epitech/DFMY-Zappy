/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** buffer.c.hpp
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>

// @brief Buffer structure
typedef struct buffer_s {
    // @brief Data of buffer
    char *data;
    // @brief Size of buffer
    size_t size;
    // @brief Number of bytes in buffer
    size_t bytes;
} buffer_t;

/**
 * @brief Create a new buffer
 * @param size Size of buffer
 * @return Created buffer or NULL if an error occurred
 */
buffer_t *buffer_new(size_t size);

/**
 * @brief Free given buffer
 * @param buffer Buffer to free
 */
void buffer_free(buffer_t *buffer);

/**
 * @brief Resize buffer
 * @param buffer Buffer to resize
 * @param new_size New size of buffer
 * @return Resized buffer or NULL if an error occurred
 */
buffer_t *buffer_resize(buffer_t *buffer, size_t new_size);

/**
 * @brief Write data to buffer
 * @param buffer Buffer to write to
 * @param data Data to write
 * @param size Size of data
 * @return Number of bytes written
 */
size_t buffer_write(buffer_t *buffer, const char *data, size_t size);

/**
 * @brief Write formatted data to buffer
 * @param buffer Buffer to write to
 * @param format Format string
 * @param args Arguments for the format string
 * @return Number of bytes written
 */
ssize_t buffer_vwritef(buffer_t *buffer, const char *format, va_list args);

/**
 * @brief Write formatted data to buffer
 * @param buffer Buffer to write to
 * @param format Format string
 * @return Number of bytes written
 */
ssize_t buffer_writef(buffer_t *buffer, const char *format, ...)
__attribute__((format(printf, 2, 3)));

/**
 * @brief Write buffer to file descriptor
 * @param buffer Buffer to write to
 * @param fd File descriptor to write to
 * @return Number of bytes written
 */
ssize_t buffer_flush(buffer_t *buffer, int fd);

/**
 * @brief Clear buffer
 * @param buffer Buffer to clear
 */
void buffer_clear(buffer_t *buffer);

/**
 * @brief Clear buffer up to a certain size
 * @param buffer Buffer to clear
 * @param size Size to clear up to
 */
void buffer_clear_size(buffer_t *buffer, size_t size);

/**
 * @brief Read from file descriptor to buffer
 * @param buffer Buffer to read to
 * @param fd File descriptor to read from
 * @return Number of bytes read
 */
ssize_t buffer_read_from(buffer_t *buffer, int fd);

/**
 * @brief Read from buffer
 * @param buffer Buffer to read from
 * @param size Size max to read
 * @return Read size
 */
size_t buffer_read(buffer_t *buffer, size_t size);

/**
 * @brief Read from buffer until delimiter
 * @param buffer Buffer to read from
 * @param delim Delimiter
 * @return Read size
 */
size_t buffer_read_delim(buffer_t *buffer, int delim);


/**
 * @brief Check if buffer is full
 * @param buffer Buffer to check
 * @return true if buffer is full, false otherwise
 */
bool buffer_is_full(buffer_t *buffer);
