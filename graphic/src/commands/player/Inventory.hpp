/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Inventory
*/

#pragma once

#include "commands/ACommand.hpp"

class PlayerInventoryCommand : public ACommand {
    public:
        PlayerInventoryCommand(Client &client, Map &map, bool &sliderChanged);
        ~PlayerInventoryCommand() = default;

        void execute(std::string &params) override;
};
