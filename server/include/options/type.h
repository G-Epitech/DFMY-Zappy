/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Options type.h
*/

#pragma once

// @brief Structure containing the options of the server
typedef struct options_t {
    // @brief The port of the server
    int port;
    // @brief The width of the map
    int width;
    // @brief The height of the map
    int height;
    // @brief The number of clients allowed to connect
    int clientsNb;
    // @brief The frequency of the server
    int freq;
    // @brief The names of the teams
    char **teams;
} options_t;
