/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Size
*/

#pragma once

#include "commands/ACommand.hpp"

class MapSizeCommand : public ACommand {
    public:
        MapSizeCommand(Client &client, Map &map, bool &sliderChanged);
        ~MapSizeCommand() = default;

        void execute(std::string &params) override;
};
