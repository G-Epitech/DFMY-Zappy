/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** End
*/

#pragma once

#include "commands/ACommand.hpp"

class GameEndCommand : public ACommand {
    public:
        GameEndCommand(Client &client, Map &map, bool &sliderChanged);
        ~GameEndCommand() = default;

        void execute(std::string &params) override;
};
