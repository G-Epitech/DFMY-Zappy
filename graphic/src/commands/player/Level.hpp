/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Level
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerLevelCommand : public ACommand {
    public:
        PlayerLevelCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerLevelCommand() = default;

        void execute(std::string &params) override;
};
