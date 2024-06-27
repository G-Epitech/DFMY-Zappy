/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Request
*/

#pragma once

#include "commands/ACommand.hpp"

class TimeRequestCommand : public ACommand {
    public:
        TimeRequestCommand(Client &client, Map &map, bool &sliderChanged);
        ~TimeRequestCommand() = default;

        void execute(std::string &params) override;
};
