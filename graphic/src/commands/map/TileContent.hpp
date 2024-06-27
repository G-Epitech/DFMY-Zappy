/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Size
*/

#pragma once

#include "commands/ACommand.hpp"

class MapTileContentCommand : public ACommand {
    public:
        MapTileContentCommand(Client &client, Map &map, bool &sliderChanged);
        ~MapTileContentCommand() = default;

        void execute(std::string &params) override;
};
