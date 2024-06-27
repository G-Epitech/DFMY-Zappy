/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Command
*/

#pragma once

#include "commands/ACommand.hpp"

class BadParametersCommand : public ACommand {
    public:
        BadParametersCommand(Client &client, Map &map, bool &sliderChanged);
        ~BadParametersCommand() = default;

        void execute(std::string &params) override;
};
