/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** log.h
*/

#pragma once

typedef enum e_log_level {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} log_level_t;

/**
 * @brief Provide an access to the current log level
 * @return Log level pointer
 */
log_level_t *log_level(void);

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
