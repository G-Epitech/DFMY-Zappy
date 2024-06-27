/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Message
*/

#pragma once

#include "commands/ACommand.hpp"

class GameMessageCommand : public ACommand {
    public:
        GameMessageCommand(Client &client, Map &map, bool &sliderChanged);
        ~GameMessageCommand() = default;

        void execute(std::string &params) override;
};
