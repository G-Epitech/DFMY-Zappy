/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Broadcast
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerBroadcastCommand : public ACommand {
    public:
        PlayerBroadcastCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerBroadcastCommand() = default;

        void execute(std::string &params) override;
    
    private:

        /**
         * @brief Create a broadcast circle
         */
        Circle _createBroadcastCircle(const Ogre::Vector3 &position);
};
