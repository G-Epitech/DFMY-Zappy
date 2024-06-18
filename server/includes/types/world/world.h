/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** World
*/

#pragma once

#include <stddef.h>
#include "map.h"
#include "chrono.h"
#include "resource.h"
#include "types/list.h"
#include "types/world/player.h"

// @brief Structure representing a Trantorian world
typedef struct world_s {
    // @brief Map of the world
    map_t *map;
    // @brief List of teams in the world
    list_t *teams;
    // @brief List of players in the world
    list_t *players;
    // @brief Clock of the world
    chrono_t chrono;
    // @brief Resources manager of the world
    resources_manager_t resources_manager;
    // @brief Delay before next predictable event in world
    time_unit_t next_event_delay;
    // @brief List of incantations in the world
    list_t *incantations;
    // @brief The current number that will be assigned to the next player
    size_t next_player_id;
} world_t;

/**
 * @brief Create a new trantorian world
 * @param map_size Size of the world map
 * @param frequency Frequency of the world clock
 * @return world structure
 */
world_t *world_new(vector2u_t map_size, size_t frequency);

/**
 * @brief Create teams in a trantorian world
 * @param world World to create teams in
 * @param teams_names Teams names
 * @param min_slots Minimum number of slots in a team
 * @return Teams success creation status
 */
bool world_create_teams(world_t *world, char **teams_names, size_t min_slots);

/**
 * @brief Free a trantorian world
 * @param world World to free
 */
void world_free(world_t *world);

/**
 * @brief Check the delay of the next event to see if it needs to be updated
 * @param world World to check
 * @param event_delay Delay of the event to check
 */
void world_register_event(world_t *world, time_unit_t event_delay);

/**
 * @brief Reset the delay of the next event to -1
 * @param world World to reset the event delay in
 */
void world_reset_event_delay(world_t *world);

/**
 * @brief Register a player in the world
 * @param world World to register the player in
 * @param player Player to register
 */
void world_player_register(world_t *world, player_t *player);

/**
 * @brief Add a player to the world
 * @param world World to add the player to
 * @param player Player to add
 * @return Success status
 */
bool world_add_player(world_t *world, player_t *player);

/**
 * @brief Remove a player from the world
 * @param world World to remove the player from
 * @param player Player to remove
 */
void world_remove_player(world_t *world, player_t *player);

/**
 * @brief Generate resources in the world
 * @param world World to generate resources in
 */
void world_routine_resources_generation(world_t *world);

/**
 * @brief Check if a team has won and send a victory message if so
 * @param team Team to check
 */
bool world_routine_team_victory(world_t *world, list_t *all_ctrls);
