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
#include "types/trantor/player.h"
#include "types/server.h"

// @brief Structure representing a Trantorian world
typedef struct world_s {
    // @brief Map of the world
    map_t *map;
    // @brief List of teams in the world
    list_t *teams;
    // @brief List of players in the world
    list_t *players;
    // @brief List of dead players in the world
    list_t *dead_players;
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
    // @brief The current number that will be assigned to the next egg
    size_t next_egg_id;
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
 * @param team Team of the player
 * @return true if player has correctly been registered,
 * false otherwise
 */
bool world_register_player(world_t *world, player_t *player, team_t *team);

/**
 * @brief Unregister a player from the world
 * @param world World to unregister the player from
 * @param player Player to unregister
 */
void world_unregister_player(world_t *world, player_t *player);

/**
 * @brief Remove a player from the world
 * @param world World to remove the player from
 * @param player Player to remove
 * @param zombie Specify if the player is a zombie and should not be
 * handled as a dead player. It will be freed.
 */
void world_kill_player(world_t *world, player_t *player, bool zombie);

/**
 * @brief Create an egg in the world for a team
 * @param world World to create the egg in
 * @param team Team of the egg
 * @param laid_by Player who laid the egg
 * @return Created egg or NULL if failed
 */
egg_t *world_add_egg(world_t *world, team_t *team, long laid_by);

/**
 * @brief Ensure a team has a minimum number of slots
 * @param world World to ensure the slots in
 * @param team Team to ensure the slots in
 * @return Number of slots that have been added
 */
size_t world_ensure_team_slots(world_t *world, team_t *team);

/**
 * @brief Kill an egg in the world
 * @param world World to kill the egg in
 * @param egg Egg to kill
 */
void world_kill_egg(world_t *world, egg_t *egg);

/**
 * @brief Start an incantation
 * @param player Player who requested the incantation
 * @param world World of the incantation
 * @return Started incantation or NULL if failed
 */
incantation_t *world_start_incantation(world_t *world, player_t *player);

/**
 * @brief Cleanup up an incantation (remove all players, remove from
 * world and free)
 * @param incantation Incantation to cleanup
 * @param world World of the incantation
 */
void world_remove_incantation(world_t *world, incantation_t *incantation);

/**
 * @brief Hatch an egg in the world and create a player
 * @param world World to hatch the egg in
 * @param egg Egg to hatch
 * @return Created player or NULL if failed
 */
player_t *world_hatch_egg(world_t *world, egg_t *egg);

/**
 * @brief Update the resources generation delay
 * @param world World to update the resources generation delay in
 */
void world_update_resources_generation_delay(world_t *world);

/**
 * @brief Kill a list of eggs and notify the server
 * @param world World to kill the eggs in
 * @param eggs List of eggs to kill
 * @param server Server to notify
 */
void world_kill_eggs(world_t *world, list_t *eggs, server_t *server);
