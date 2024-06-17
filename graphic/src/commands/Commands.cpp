/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#include <iostream>
#include "Commands.hpp"
#include "utils/String.hpp"

std::vector<std::string> stonesNames = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

void Commands::_addItemsToTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity)
{
    Ogre::SceneNode *node = tile.node;
    if (!node || node->numAttachedObjects() == 0)
        return;
    auto tileSize = node->getAttachedObject(0)->getBoundingBox().getSize();
    Ogre::Vector3 pos = node->getPosition();
    Ogre::Vector3 size = node->getAttachedObject(0)->getBoundingBox().getSize();

    for (int i = 0; i < quantity; i++) {
        Ogre::Entity* cubeEntity = scnMgr->createEntity(itemName + ".mesh");
        Ogre::SceneNode* itemNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        auto itemSize = cubeEntity->getBoundingBox().getSize();
        itemNode->attachObject(cubeEntity);

        float randX = pos.x + static_cast<float>(std::rand()) / RAND_MAX * tileSize.x - tileSize.x / 2.0f;
        float randZ = pos.z + static_cast<float>(std::rand()) / RAND_MAX * tileSize.z - tileSize.z / 2.0f;
        float itemY = itemSize.y / 2.0f * 0.1;

        itemNode->setPosition(randX, itemY, randZ);
        itemNode->setScale(0.1f, 0.1f, 0.1f);
        tile.items[itemName].push_back(itemNode);
    }
}

void Commands::_removeItemsFromTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity)
{
    for (int i = 0; i < quantity; i++) {
        if (tile.items[itemName].empty())
            return;
        Ogre::SceneNode *node = tile.items[itemName].back();
        tile.items[itemName].pop_back();
        scnMgr->destroySceneNode(node);
    }
}

Ogre::SceneNode *Commands::_createPlayerItem(Ogre::SceneManager *scnMgr, Tile &tile)
{
    Ogre::Entity *cubeEntity = scnMgr->createEntity("food.mesh");
    Ogre::SceneNode *node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(cubeEntity);

    Ogre::AxisAlignedBox aab = cubeEntity->getBoundingBox();
    Ogre::Vector3 size = aab.getSize();

    float randX = tile.node->getPosition().x + static_cast<float>(std::rand()) / RAND_MAX * size.x - size.x / 2.0f;
    float randZ = tile.node->getPosition().z + static_cast<float>(std::rand()) / RAND_MAX * size.z - size.z / 2.0f;
    float itemY = size.y;

    node->setPosition(randX, itemY, randZ);
    node->setScale(PLAYER_SCALE, PLAYER_SCALE, PLAYER_SCALE);

    return node;
}

void Commands::map_size(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 2)
        return;
    map.width = std::stoi(args[0]);
    map.height = std::stoi(args[1]);
    int posx = map.width / 2;
    int posy = map.height / 2;
    for (int i = 0; i < map.width; i++) {
        std::vector<Tile> row;
        posy = map.height / 2;
        for (int j = 0; j < map.height; j++) {
            Ogre::Entity *cubeEntity = scnMgr->createEntity("Cube.mesh");
            Ogre::SceneNode *node = scnMgr->getRootSceneNode()->createChildSceneNode();
            node->attachObject(cubeEntity);

            Ogre::AxisAlignedBox aab = cubeEntity->getBoundingBox();
            Ogre::Vector3 size = aab.getSize();
            node->setPosition(posx * size.x, -size.y / 2.0, posy * size.z);

            Tile tile;

            for (int i = 0; i < stonesNames.size(); i++) {
                tile.items[stonesNames[i]] = {};
            }
            tile.node = node;
            row.push_back(tile);
            posy = posy - 1;
        }
        map.tiles.push_back(row);
        posx = posx - 1;
    }
}

void Commands::tile_content(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 9)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);
    if (x < 0 || x >= map.width || y < 0 || y >= map.height)
        return;
    int food = std::stoi(args[2]) - map.tiles[x][y].items["food"].size();
    std::vector<int> stones;
    for (int i = 0; i < stonesNames.size(); i++) {
        stones.push_back(std::stoi(args[3 + i]) - map.tiles[x][y].items[stonesNames[i]].size());
    }

    if (food > 0)
        _addItemsToTile(map.tiles[x][y], scnMgr, "food", food);
    else if (food < 0)
        _removeItemsFromTile(map.tiles[x][y], scnMgr, "food", -food);
    for (int i = 0; i < stonesNames.size(); i++) {
        if (stones[i] > 0)
            _addItemsToTile(map.tiles[x][y], scnMgr, stonesNames[i], stones[i]);
        else if (stones[i] < 0)
            _removeItemsFromTile(map.tiles[x][y], scnMgr, stonesNames[i], -stones[i]);
    }
}

void Commands::teams_names(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    map.teams.push_back(args[0]);
}

void Commands::player_connect(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 6)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    int orientation = std::stoi(args[3]);
    int level = std::stoi(args[4]);
    std::string team = args[5];

    if (x < 0 || x >= map.width || y < 0 || y >= map.height)
        return;

    for (const auto& player : map.players) {
        if (player.id == id) {
            return;
        }
    }

    Player player;
    player.id = id;
    player.node = _createPlayerItem(scnMgr, map.tiles[x][y]);
    player.orientation = orientation;
    player.level = level;
    player.team = team;
    player.position = {x, y};
    map.players.push_back(player);
}

void Commands::player_position(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 4)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    if (x < 0 || x >= map.width || y < 0 || y >= map.height)
        return;

    for (auto &player : map.players) {
        if (player.id == id) {
            player.position.x = x;
            player.position.y = y;
            if (!player.node)
                player.node = _createPlayerItem(scnMgr, map.tiles[x][y]);
            player.node->setPosition(map.tiles[x][y].node->getPosition().x, player.node->getPosition().y, map.tiles[x][y].node->getPosition().z);
            return;
        }
    }

    Player player;
    player.id = id;
    player.node = _createPlayerItem(scnMgr, map.tiles[x][y]);
    player.position.x = x;
    player.position.y = y;
    map.players.push_back(player);

    client.write("pin " + std::to_string(id) + "\n");
    client.write("plv " + std::to_string(id) + "\n");
}

void Commands::player_level(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 2)
        return;
    int id = std::stoi(args[0]);
    int level = std::stoi(args[1]);

    for (auto &player : map.players) {
        if (player.id == id) {
            player.level = level;
            return;
        }
    }

    Player player;
    player.id = id;
    player.level = level;
    map.players.push_back(player);

    client.write("pin " + std::to_string(id) + "\n");
    client.write("ppo " + std::to_string(id) + "\n");
}

void Commands::player_inventory(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 10)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);

    if (x < 0 || x >= map.width || y < 0 || y >= map.height)
        return;

    Inventory inventory;
    inventory.food = std::stoi(args[3]);
    inventory.linemate = std::stoi(args[4]);
    inventory.deraumere = std::stoi(args[5]);
    inventory.sibur = std::stoi(args[6]);
    inventory.mendiane = std::stoi(args[7]);
    inventory.phiras = std::stoi(args[8]);
    inventory.thystame = std::stoi(args[9]);

    for (auto &player : map.players) {
        if (player.id == id) {
            player.inventory = inventory;
            return;
        }
    }

    Player player;
    player.id = id;
    player.inventory = inventory;
    map.players.push_back(player);

    client.write("pin " + std::to_string(id) + "\n");
    client.write("plv " + std::to_string(id) + "\n");
}

void Commands::player_eject(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int id = std::stoi(args[0]);

    // TODO: Implement player ejection
    std::cout << "Player " << id << " have been ejected or eject others?" << std::endl;
}

void Commands::broadcast(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client)
{
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() < 2)
        return;
    int id = std::stoi(args[0]);
    std::string message = args[1];

    // TODO: Implement broadcast animation
    std::cout << "Player " << id << " broadcasted: " << message << std::endl;
}
