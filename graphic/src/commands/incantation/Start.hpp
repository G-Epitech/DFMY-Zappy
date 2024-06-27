/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Start
*/

#pragma once

#include "commands/ACommand.hpp"

class IncantationStartCommand : public ACommand {
    public:
        IncantationStartCommand(Client &client, Map &map, bool &sliderChanged);
        ~IncantationStartCommand() = default;

        void execute(std::string &params) override;
    
    private:

        /**
         * @brief Create an incantation sphere
         */
        Sphere _createIncantationSphere(const Ogre::Vector3 &position);
};
