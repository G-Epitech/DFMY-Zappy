/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Fork
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerForkCommand : public ACommand {
    public:
        PlayerForkCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerForkCommand() = default;

        void execute(std::string &params) override;
};
