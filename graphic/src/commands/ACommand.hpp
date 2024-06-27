/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ACommand
*/

#pragma once

#include "types/Map.hpp"
#include "utils/String.hpp"
#include "client/Client.hpp"
#include "constants/Tile.hpp"
#include "constants/Player.hpp"
#include "interfaces/ICommand.hpp"
#include "constants/Broadcast.hpp"
#include "constants/Resources.hpp"
#include "constants/Incantation.hpp"

class ACommand : public ICommand {
    public:

        /**
         * @brief Construct a new ACommand object
         * @param client Client object to send commands to the server
         * @param map Map object to update the game state
         * @param sliderChanged Boolean to check if the slider was changed
         */
        ACommand(Client &client, Map &map, bool &sliderChanged);

        /**
         * @brief Destroy the ACommand object
         */
        ~ACommand();

        /**
         * @brief Execute a command
         * @param params The parameters of the command
         */
        virtual void execute(std::string &params) = 0;

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

        /**
         * @brief Set the OgreBites::Slider object
         * @param timeSlider The OgreBites::Slider object
         */
        void setSlider(OgreBites::Slider* timeSlider);

        /**
         * @brief Set the sliderChanged boolean
         * @param sliderChanged The boolean to set
         */
        void setSliderChanged(bool &sliderChanged);

    protected:
        Client &_client;
        Map &_map;
        bool &_sliderChanged;
        Ogre::SceneManager* _scnMgr;
        OgreBites::TextBox* _logs;
        OgreBites::Slider* _timeSlider;
};
