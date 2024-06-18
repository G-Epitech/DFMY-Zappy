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

#define BROADCAST_CIRCLE_MAX_RADIUS 5.0f
#define BROADCAST_CIRCLE_SEGMENTS 100

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

    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;

private:
    Client _client;
    OgreBites::TrayManager *trayManager;
    Ogre::SceneManager *scnMgr;
    Map _map;
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
};
