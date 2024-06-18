/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#pragma once

#include "types/Map.hpp"
#include "client/Client.hpp"

#define PLAYER_SCALE 0.6f

class Commands {
public:

    static void map_size(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void tile_content(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void teams_names(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_connect(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_position(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_level(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_inventory(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_eject(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void broadcast(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void incantation_start(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void incantation_end(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_laying_egg(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_resource_drop(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_resource_take(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_death(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void player_egg_laid(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void egg_death(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void egg_hatching(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void time_unit_request(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void time_unit_modification(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void end_game(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void unknown_command(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void command_parameters(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);

private:
    static void _addItemsToTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity);
    static void _removeItemsFromTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity);
    static Ogre::SceneNode *_createPlayerItem(Ogre::SceneManager *scnMgr, Tile &tile);
};
