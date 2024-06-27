/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Hatch
*/

#pragma once

#include "commands/ACommand.hpp"

class EggHatchCommand : public ACommand {
    public:
        EggHatchCommand(Client &client, Map &map, bool &sliderChanged);
        ~EggHatchCommand() = default;

        void execute(std::string &params) override;
};
