/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** End
*/

#pragma once

#include "commands/ACommand.hpp"

class IncantationEndCommand : public ACommand {
    public:
        IncantationEndCommand(Client &client, Map &map, bool &sliderChanged);
        ~IncantationEndCommand() = default;

        void execute(std::string &params) override;
};
