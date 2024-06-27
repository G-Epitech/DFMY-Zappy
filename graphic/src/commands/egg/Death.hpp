/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Death
*/

#pragma once

#include "commands/ACommand.hpp"

class EggDeathCommand : public ACommand {
    public:
        EggDeathCommand(Client &client, Map &map, bool &sliderChanged);
        ~EggDeathCommand() = default;

        void execute(std::string &params) override;
};
