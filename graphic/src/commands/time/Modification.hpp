/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Modification
*/

#pragma once

#include "commands/ACommand.hpp"

class TimeModificationCommand : public ACommand {
    public:
        TimeModificationCommand(Client &client, Map &map, bool &sliderChanged);
        ~TimeModificationCommand() = default;

        void execute(std::string &params) override;
};
