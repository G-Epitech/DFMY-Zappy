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

#include "commands/player/Connect.hpp"
#include "commands/player/Position.hpp"
#include "commands/player/Level.hpp"
#include "commands/player/Inventory.hpp"
#include "commands/player/Eject.hpp"
#include "commands/player/Broadcast.hpp"
#include "commands/player/Fork.hpp"
#include "commands/player/Drop.hpp"
#include "commands/player/Take.hpp"
#include "commands/player/Death.hpp"

#include "commands/incantation/Start.hpp"
#include "commands/incantation/End.hpp"

CommandFactory::CommandFactory(Client &client, Map &map, bool &sliderChanged) {
    commandRegister("msz", [&](){ return std::make_unique<MapSizeCommand>(client, map, sliderChanged); });
    commandRegister("bct", [&](){ return std::make_unique<MapTileCommand>(client, map, sliderChanged); });
    commandRegister("tna", [&](){ return std::make_unique<TeamsNamesCommand>(client, map, sliderChanged); });
    commandRegister("pnw", [&](){ return std::make_unique<PlayerConnectCommand>(client, map, sliderChanged); });
    commandRegister("ppo", [&](){ return std::make_unique<PlayerPositionCommand>(client, map, sliderChanged); });
    commandRegister("plv", [&](){ return std::make_unique<PlayerLevelCommand>(client, map, sliderChanged); });
    commandRegister("pin", [&](){ return std::make_unique<PlayerInventoryCommand>(client, map, sliderChanged); });
    commandRegister("pex", [&](){ return std::make_unique<PlayerEjectCommand>(client, map, sliderChanged); });
    commandRegister("pbc", [&](){ return std::make_unique<PlayerBroadcastCommand>(client, map, sliderChanged); });
    commandRegister("pic", [&](){ return std::make_unique<IncantationStartCommand>(client, map, sliderChanged); });
    commandRegister("pie", [&](){ return std::make_unique<IncantationEndCommand>(client, map, sliderChanged); });
    commandRegister("pfk", [&](){ return std::make_unique<PlayerForkCommand>(client, map, sliderChanged); });
    commandRegister("pdr", [&](){ return std::make_unique<PlayerDropCommand>(client, map, sliderChanged); });
    commandRegister("pgt", [&](){ return std::make_unique<PlayerTakeCommand>(client, map, sliderChanged); });
    commandRegister("pdi", [&](){ return std::make_unique<PlayerDeathCommand>(client, map, sliderChanged); });
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
