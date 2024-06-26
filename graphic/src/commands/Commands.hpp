/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#pragma once

#include <memory>
#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreTrays.h>
#include "types/Map.hpp"
#include "../client/Client.hpp"
#include "constants/Broadcast.hpp"
#include "constants/Player.hpp"

class Commands {
public:

    /**
     * @brief Construct a new Commands object
     * @param client Client object to send commands to the server
     * @param map Map object to update the game state
     * @param scnMgr Ogre::SceneManager object to create entities
     * @param logs OgreBites::TextBox object to display logs
     */
    Commands(Client &client, Map &map, Ogre::SceneManager* scnMgr, OgreBites::TextBox* logs);

    /**
     * @brief Destroy the Commands object
     */
    ~Commands();

    /**
     * @brief Execute a command
     * @param command The command to execute
     * @param params The parameters of the command
     */
    void execute(std::string &command, std::string &params);

    /**
     * @brief Set the Ogre::SceneManager object
     * @param scnMgr The Ogre::SceneManager object
     */
    void setScnMgr(Ogre::SceneManager* scnMgr);

    /**
     * @brief Set the OgreBites::TextBox object
     * @param logs The OgreBites::TextBox object
     */
    void setLogs(OgreBites::TextBox* logs);

    void mapSize(std::string &params);
    void tileContent(std::string &params);
    void teamsNames(std::string &params);
    void playerConnect(std::string &params);
    void playerPosition(std::string &params);
    void playerLevel(std::string &params);
    void playerInventory(std::string &params);
    void playerEject(std::string &params);
    void broadcast(std::string &params);
    void incantationStart(std::string &params);
    void incantationEnd(std::string &params);
    void playerLayingEgg(std::string &params);
    void playerResourceDrop(std::string &params);
    void playerResourceTake(std::string &params);
    void playerDeath(std::string &params);
    void playerEggLaid(std::string &params);
    void eggDeath(std::string &params);
    void eggHatching(std::string &params);
    void timeUnitRequest(std::string &params);
    void timeUnitModification(std::string &params);
    void endGame(std::string &params);
    void unknownCommand(std::string &params);
    void commandParameters(std::string &params);

private:
    Circle _createBroadcastCircle(const Ogre::Vector3 &position);
    Sphere _createIncantationSphere(const Ogre::Vector3 &position);

    void _addLogMessage(const std::string& message);

    Client &_client;
    Map &_map;
    Ogre::SceneManager* _scnMgr;
    std::map<std::string, std::function<void(std::string &)>> _commands;
    OgreBites::TextBox* _logs;
};
