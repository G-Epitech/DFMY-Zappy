/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#pragma once

#include "types/Map.hpp"
#include "../client/Client.hpp"
#include "constants/Broadcast.hpp"
#include "constants/Player.hpp"

class Commands {
public:

    static void mapSize(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void tileContent(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void teamsNames(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerConnect(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerPosition(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerLevel(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerInventory(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerEject(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void broadcast(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void incantationStart(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void incantationEnd(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerLayingEgg(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerResourceDrop(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerResourceTake(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerDeath(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void playerEggLaid(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void eggDeath(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void eggHatching(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void timeUnitRequest(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void timeUnitModification(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void endGame(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void unknownCommand(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);
    static void commandParameters(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client);

private:
    static void _addItemsToTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity);
    static void _removeItemsFromTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity);
    static Ogre::SceneNode *_createPlayerItem(Ogre::SceneManager *scnMgr, Tile &tile, const std::string& teamName, Teams &teams);
    static Circle _createBroadcastCircle(Ogre::SceneManager *scnMgr, const Ogre::Vector3 &position);
    static Sphere _createIncantationSphere(Ogre::SceneManager *scnMgr, const Ogre::Vector3 &position);
};
