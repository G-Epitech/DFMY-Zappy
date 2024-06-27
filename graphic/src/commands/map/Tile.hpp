/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Size
*/

#pragma once

#include "commands/ACommand.hpp"

class MapTileCommand : public ACommand {
    public:
        MapTileCommand(Client &client, Map &map, bool &sliderChanged);
        ~MapTileCommand() = default;

        void execute(std::string &params) override;
};
