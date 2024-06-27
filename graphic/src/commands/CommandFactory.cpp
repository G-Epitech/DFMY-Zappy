/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** CommandFactory
*/

#include "CommandFactory.hpp"

#include "commands/map/Size.hpp"
#include "commands/map/Tile.hpp"

#include "commands/teams/Names.hpp"

CommandFactory::CommandFactory(Client &client, Map &map, bool &sliderChanged) {
    commandRegister("msz", [&](){ return std::make_unique<MapSizeCommand>(client, map, sliderChanged); });
    commandRegister("bct", [&](){ return std::make_unique<MapTileCommand>(client, map, sliderChanged); });
    commandRegister("tna", [&](){ return std::make_unique<TeamsNamesCommand>(client, map, sliderChanged); });
}

CommandFactory::~CommandFactory() = default;

void CommandFactory::commandRegister(
        const std::string &commandName,
        std::function<std::unique_ptr<ICommand>()> constructor) {
    _commands[commandName] = std::move(constructor);
}

std::unique_ptr<ICommand> CommandFactory::createCommand(const std::string &commandName) {
    if (_commands.find(commandName) == _commands.end())
        return nullptr;
    return _commands[commandName]();
}
