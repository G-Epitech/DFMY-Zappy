/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** log.c
*/

#include "log.h"

log_level_t *log_level(void)
{
    static log_level_t level = LOG_INFO;

    return &level;
}
