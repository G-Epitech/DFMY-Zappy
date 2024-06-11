/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** log.h
*/

#pragma once

typedef enum e_log_level {
    INFO,
    WARN,
    ERROR,
    DEBUG
} log_level_t;

/**
 * @brief Log a message with the DEBUG level
 * @param format Format of the message
 */
void log_debug(const char *format, ...) __attribute__((format(printf, 1, 2)));

/**
 * @brief Log a message with the WARN level
 * @param format Format of the message
 */
void log_warn(const char *format, ...) __attribute__((format(printf, 1, 2)));

/**
 * @brief Log a message with the ERROR level
 * @param format Format of the message
 */
void log_error(const char *format, ...) __attribute__((format(printf, 1, 2)));

/**
 * @brief Log a message with the INFO level
 * @param format Format of the message
 */
void log_info(const char *format, ...) __attribute__((format(printf, 1, 2)));
