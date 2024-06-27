/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Command
*/

#pragma once

#include "commands/ACommand.hpp"

class BadCommandCommand : public ACommand {
    public:
        BadCommandCommand(Client &client, Map &map, bool &sliderChanged);
        ~BadCommandCommand() = default;

        void execute(std::string &params) override;
};
