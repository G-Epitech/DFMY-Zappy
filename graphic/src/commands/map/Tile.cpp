/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** MapTileCommand
*/

#include "Tile.hpp"

MapTileCommand::MapTileCommand(Client &client, Map &map, bool &sliderChanged)
    : ACommand(client, map, sliderChanged) {}

void MapTileCommand::execute(std::string &params) {
    std::vector<std::string> args = Utils::StringUtils::split(params, ' ');

    if (args.size() != 9)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);
    if (x < 0 || x >= _map.width || y < 0 || y >= _map.height)
        return;
    int food = std::stoi(args[2]) - _map.tiles[x][y]->items["food"].size();
    std::vector<int> stones;
    for (int i = 0; i < stonesNames.size() && i + 3 < args.size(); i++) {
        stones.push_back(std::stoi(args[3 + i]) - _map.tiles[x][y]->items[stonesNames[i]].size());
    }

    if (food > 0)
        _map.tiles[x][y]->addItemEntity("food", food, _scnMgr);
    else if (food < 0)
        _map.tiles[x][y]->removeItemEntity("food", -food, _scnMgr);
    for (int i = 0; i < stonesNames.size(); i++) {
        if (stones[i] > 0)
            _map.tiles[x][y]->addItemEntity(stonesNames[i], stones[i], _scnMgr);
        else if (stones[i] < 0)
            _map.tiles[x][y]->removeItemEntity(stonesNames[i], -stones[i], _scnMgr);
    }
}
