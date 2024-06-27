/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Position
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerPositionCommand : public ACommand {
    public:
        PlayerPositionCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerPositionCommand() = default;

        void execute(std::string &params) override;
};
