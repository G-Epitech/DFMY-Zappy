/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** incantation.h
*/

#pragma once

#include "types/list.h"
#include "types/controller.h"

// @brief Represents a world incantation
typedef struct incantation_s {
    // @brief List of players involved in the incantation
    list_t *players;
    // @brief The player who requested the incantation
    player_controller_t *requester;
    // @brief The level of the incantation
    unsigned int level;
} incantation_t;

/**
 * @brief Create a new incantation
 * @param requester Requester of the incantation
 * @param level Desired level of the incantation
 * @return Created incantation or NULL if failed
 */
incantation_t *incantation_new(player_controller_t *requester,
    unsigned int level);

/**
* @brief Free given incantation
* @param incantation Incantation to free
*/
void incantation_free(incantation_t *incantation);

/**
 * @brief Free given incantation as node data
 * @param incantation Incantation to free as node data
 */
void incantation_free_as_node_data(node_data_t incantation);
