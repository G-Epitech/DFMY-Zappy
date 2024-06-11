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
 * @brief Log a message
 * @param msg the message to log_message
 * @param level the level of the log_message
*/
void log_message(log_level_t level, const char *format, ...);
