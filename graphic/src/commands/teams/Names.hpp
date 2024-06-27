/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Name
*/

#pragma once

#include "commands/ACommand.hpp"

class TeamsNamesCommand : public ACommand {
    public:
        TeamsNamesCommand(Client &client, Map &map, bool &sliderChanged);
        ~TeamsNamesCommand() = default;

        void execute(std::string &params) override;
};
