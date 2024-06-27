/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Death
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerDeathCommand : public ACommand {
    public:
        PlayerDeathCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerDeathCommand() = default;

        void execute(std::string &params) override;
};
