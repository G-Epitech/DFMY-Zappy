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

class App : public OgreBites::ApplicationContext, public OgreBites::InputListener {
public:
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

private:
    /**
     * @brief Load resources of the application
     */
    static void _loadResources();

    OgreBites::TrayManager *trayManager;
};
