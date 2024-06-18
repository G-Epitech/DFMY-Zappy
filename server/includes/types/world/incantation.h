/*
** EPITECH PROJECT, 2024
** zappy_server
** File description:
** incantation.h
*/

#pragma once

#include "types/list.h"
#include "types/controller.h"
#include "map.h"

// @brief Duration of an incantation
#define INCANTATION_DURATION 300

// @brief Represents a world incantation
typedef struct incantation_s {
    // @brief List of players involved in the incantation
    list_t *players;
    // @brief Incantation cooldown
    time_unit_t cooldown;
    // @brief Requester
    player_t *requester;
    // @brief The level of the incantation
    unsigned int level;
} incantation_t;

/**
 * @brief Create a new incantation
 * @param cell Cell on which the incantation is happening
 * @param level Desired level of the incantation
 * @param requester Player who requested the incantation
 * @return Created incantation or NULL if failed
 */
incantation_t *incantation_new(unsigned int level, player_t *requester);

/**
* @brief Free given incantation
* @param incantation Incantation to free
*/
void incantation_free(incantation_t *incantation);

/**
 * @brief Add a player to the incantation
 * @param incantation Incantation to add the player to
 * @param player Player to add to the incantation
 */
void incantation_remove_player(incantation_t *incantation, player_t *player);

/**
 * @brief Add a player to the incantation
 * @param incantation Incantation to add the player to
 * @param player Player to add to the incantation
 * @return true if the player was added, false otherwise
 */
bool incantation_add_player(incantation_t *incantation, player_t *player);

/**
 * @brief Free given incantation as node data
 * @param incantation Incantation to free as node data
 */
void incantation_free_as_node_data(node_data_t incantation);
