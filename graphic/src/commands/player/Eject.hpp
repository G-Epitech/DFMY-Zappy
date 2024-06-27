/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Eject
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerEjectCommand : public ACommand {
    public:
        PlayerEjectCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerEjectCommand() = default;

        void execute(std::string &params) override;
};
