/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Take
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerTakeCommand : public ACommand {
    public:
        PlayerTakeCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerTakeCommand() = default;

        void execute(std::string &params) override;
};
