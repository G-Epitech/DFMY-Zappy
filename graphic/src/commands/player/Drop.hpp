/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Drop
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerDropCommand : public ACommand {
    public:
        PlayerDropCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerDropCommand() = default;

        void execute(std::string &params) override;
};
