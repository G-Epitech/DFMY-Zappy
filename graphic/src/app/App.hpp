/*
** EPITECH PROJECT, 2024
** App.hpp
** File description:
** App class
*/

#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreTrays.h>
#include "client/Client.hpp"
#include "types/Map.hpp"

class App : public OgreBites::ApplicationContext, public OgreBites::InputListener {
public:

    /**
     * @brief Construct a new App object
     */
    App();

    /**
     * @brief Setup the application
     */
    void setup() override;

    /**
     * @brief Key pressed event
     * @param evt Keyboard event
     * @return true if the event was handled
     */
    bool keyPressed(const OgreBites::KeyboardEvent &evt) override;

    /**
     * @brief Frame rendering queued event
     * @param evt Frame event
     * @return true if the event was handled
     */
    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;

private:
    /// @brief Client object used to communicate with the server
    Client _client;

    /// @brief Tray manager used to display GUI elements
    OgreBites::TrayManager *trayManager;

    /// @brief Scene manager used to manage the scene
    Ogre::SceneManager *scnMgr;

    /// @brief Map of the game with all the tiles, players...
    Map _map;

    /// @brief Map of commands received from the server
    std::map<std::string, std::function<void(std::string &, Map &, Ogre::SceneManager *, Client &)>> _commands;

    /**
     * @brief Load resources of the application
     */
    static void _loadResources();

    /**
     * @brief Update the map
     * @param command Command received from the server
     */
    void _updateMap(std::string &command);

    /**
     * @brief Update the broadcast circles
     * @param evt Frame event
     */
    void _updateBroadcastCircles(const Ogre::FrameEvent &evt);
};
