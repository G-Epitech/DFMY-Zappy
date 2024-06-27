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

        void setScnMgr(Ogre::SceneManager* scnMgr) override;

        void setLogs(OgreBites::TextBox* logs) override;

        void setSlider(OgreBites::Slider* timeSlider) override;

    protected:
        Client &_client;
        Map &_map;
        bool &_sliderChanged;
        Ogre::SceneManager* _scnMgr;
        OgreBites::TextBox* _logs;
        OgreBites::Slider* _timeSlider;

        void _addLogMessage(const std::string &message);
};
