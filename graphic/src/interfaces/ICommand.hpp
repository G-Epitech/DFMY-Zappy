/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ICommand
*/

#pragma once

#include <Ogre.h>
#include <OgreTrays.h>
#include <OgreApplicationContext.h>

class ICommand {
    public:

        /**
         * @brief Destroy the ICommand object
         */
        virtual ~ICommand() = default;

        /**
         * @brief Execute a command
         * @param params The parameters of the command
         */
        virtual void execute(std::string &params) = 0;

        /**
         * @brief Set the Ogre::SceneManager object
         * @param scnMgr The Ogre::SceneManager object
         */
        virtual void setScnMgr(Ogre::SceneManager* scnMgr) = 0;

        /**
         * @brief Set the OgreBites::TextBox object
         * @param logs The OgreBites::TextBox object
         */
        virtual void setLogs(OgreBites::TextBox* logs) = 0;

        /**
         * @brief Set the OgreBites::Slider object
         * @param timeSlider The OgreBites::Slider object
         */
        virtual void setSlider(OgreBites::Slider* timeSlider) = 0;
};
