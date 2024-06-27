/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Laid
*/

#pragma once

#include "commands/ACommand.hpp"

class EggLaidCommand : public ACommand {
    public:
        EggLaidCommand(Client &client, Map &map, bool &sliderChanged);
        ~EggLaidCommand() = default;

        void execute(std::string &params) override;
};
