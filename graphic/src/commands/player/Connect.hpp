/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Connect
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerConnectCommand : public ACommand {
    public:
        PlayerConnectCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerConnectCommand() = default;

        void execute(std::string &params) override;
};
