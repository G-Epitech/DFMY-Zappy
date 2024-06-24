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
std::vector<std::string> playerModels = {"Barbar.mesh", "Queen.mesh"};

void Commands::_addItemsToTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity) {
    Ogre::SceneNode *node = tile.node;
    if (!node || node->numAttachedObjects() == 0)
        return;
    auto tileSize = node->getAttachedObject(0)->getBoundingBox().getSize();
    Ogre::Vector3 pos = node->getPosition();
    Ogre::Vector3 size = node->getAttachedObject(0)->getBoundingBox().getSize();

    for (int i = 0; i < quantity; i++) {
        Ogre::Entity *cubeEntity = scnMgr->createEntity(itemName + ".mesh");
        Ogre::SceneNode *itemNode = scnMgr->getRootSceneNode()->createChildSceneNode();
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

void Commands::_removeItemsFromTile(Tile &tile, Ogre::SceneManager *scnMgr, const std::string &itemName, int quantity) {
    for (int i = 0; i < quantity; i++) {
        if (tile.items[itemName].empty())
            return;
        Ogre::SceneNode *node = tile.items[itemName].back();
        tile.items[itemName].pop_back();
        scnMgr->destroySceneNode(node);
    }
}

Ogre::SceneNode *Commands::_createPlayerItem(Ogre::SceneManager *scnMgr, Tile &tile, const std::string& teamName, Teams &teams) {
    std::size_t teamIndex = teams.teamIndex(teamName);

    if (teamIndex >= playerModels.size())
        teamIndex = 0;
    Ogre::Entity *cubeEntity = scnMgr->createEntity(playerModels[teamIndex]);
    Ogre::SceneNode *node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(cubeEntity);

    Ogre::AxisAlignedBox aab = cubeEntity->getBoundingBox();
    Ogre::Vector3 size = aab.getSize();

    float randX = tile.node->getPosition().x + static_cast<float>(std::rand()) / RAND_MAX * size.x - size.x / 2.0f;
    float randZ = tile.node->getPosition().z + static_cast<float>(std::rand()) / RAND_MAX * size.z - size.z / 2.0f;
    float itemY = size.y / 2.0f * PLAYER_SCALE;

    node->setPosition(randX, itemY, randZ);
    node->setScale(PLAYER_SCALE, PLAYER_SCALE, PLAYER_SCALE);

    return node;
}

Circle Commands::_createBroadcastCircle(Ogre::SceneManager *scnMgr, const Ogre::Vector3 &position) {
    Circle circle;
    circle.circle = scnMgr->createManualObject();
    circle.node = scnMgr->getRootSceneNode()->createChildSceneNode();
    circle.node->attachObject(circle.circle);
    circle.node->setPosition(position);
    circle.radius = 0;

    circle.circle->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
    for (int i = 0; i <= BROADCAST_CIRCLE_SEGMENTS; ++i) {
        float angle = Ogre::Math::TWO_PI * i / BROADCAST_CIRCLE_SEGMENTS;
        circle.circle->position(Ogre::Math::Cos(angle) * circle.radius, 0, Ogre::Math::Sin(angle) * circle.radius);
    }
    circle.circle->end();

    return circle;
}

Sphere Commands::_createIncantationSphere(Ogre::SceneManager *scnMgr, const Ogre::Vector3 &position) {
    Sphere sphere;
    sphere.sphere = scnMgr->createManualObject();
    sphere.node = scnMgr->getRootSceneNode()->createChildSceneNode();
    sphere.node->attachObject(sphere.sphere);
    sphere.node->setPosition(position);

    return sphere;
}

void Commands::mapSize(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
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

void Commands::tileContent(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 9)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);
    if (x < 0 || x >= map.width || y < 0 || y >= map.height)
        return;
    int food = std::stoi(args[2]) - map.tiles[x][y].items["food"].size();
    std::vector<int> stones;
    for (int i = 0; i < stonesNames.size() && i + 3 < args.size(); i++) {
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

void Commands::teamsNames(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;

    for (const auto &arg: args) {
        map.teams.addTeam(arg);
    }
}

void Commands::playerConnect(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
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

    for (const auto &player: map.players) {
        if (player.id == id) {
            return;
        }
    }

    Player player;
    player.id = id;
    player.node = _createPlayerItem(scnMgr, map.tiles[x][y], team, map.teams);
    player.orientation = orientation;
    player.level = level;
    player.team = team;
    player.position = {x, y};
    map.players.push_back(player);
}

void Commands::playerPosition(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 4)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    int orientation = std::stoi(args[3]);
    if (x < 0 || x >= map.width || y < 0 || y >= map.height)
        return;

    for (auto &player: map.players) {
        if (player.id == id) {
            player.position.x = x;
            player.position.y = y;
            player.orientation = orientation;
            if (!player.node)
                player.node = _createPlayerItem(scnMgr, map.tiles[x][y], player.team, map.teams);
            player.node->setPosition(map.tiles[x][y].node->getPosition().x, player.node->getPosition().y,
                                     map.tiles[x][y].node->getPosition().z);
            return;
        }
    }

    Player player;
    player.id = id;
    player.node = _createPlayerItem(scnMgr, map.tiles[x][y], player.team, map.teams);
    player.position.x = x;
    player.position.y = y;
    player.orientation = orientation;
    map.players.push_back(player);

    // Because it's a new player, we need to get its level and inventory
    client.write("pin " + std::to_string(id) + "\n");
    client.write("plv " + std::to_string(id) + "\n");
}

void Commands::playerLevel(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 2)
        return;
    int id = std::stoi(args[0]);
    int level = std::stoi(args[1]);

    for (auto &player: map.players) {
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

void Commands::playerInventory(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
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

    for (auto &player: map.players) {
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

void Commands::playerEject(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int id = std::stoi(args[0]);

    // TODO: Implement player ejection
    std::cout << "Player " << id << " have been ejected or eject others?" << std::endl;
}

void Commands::broadcast(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() < 2)
        return;
    int id = std::stoi(args[0]);
    std::string message = args[1];

    for (auto &player: map.players) {
        if (player.id == id) {
            Circle circle = _createBroadcastCircle(scnMgr, player.node->getPosition());
            map.broadcastCircles.push_back(circle);
            return;
        }
    }
}

void Commands::incantationStart(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() < 3)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);
    int level = std::stoi(args[2]);

    // TODO: Implement incantation animation
    Sphere sphere = _createIncantationSphere(scnMgr, map.tiles[x][y].node->getPosition());
    map.incantationSpheres.push_back(sphere);
}

void Commands::incantationEnd(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() < 3)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);
    int level = std::stoi(args[2]);

    // TODO: Implement incantation animation
    for (auto &sphere: map.incantationSpheres) {
        if (sphere.node->getPosition() == map.tiles[x][y].node->getPosition()) {
            scnMgr->destroySceneNode(sphere.node);
            map.incantationSpheres.erase(
                    std::remove(map.incantationSpheres.begin(), map.incantationSpheres.end(), sphere),
                    map.incantationSpheres.end());
            return;
        }
    }
}

void Commands::playerLayingEgg(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int player_id = std::stoi(args[0]);

    // TODO: Implement egg laying animation
}

void Commands::playerResourceDrop(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 3)
        return;
    int player_id = std::stoi(args[0]);
    std::string resource = args[1];
    int quantity = std::stoi(args[2]);

    for (auto &player: map.players) {
        if (player.id == player_id) {
            _addItemsToTile(map.tiles[player.position.x][player.position.y], scnMgr, resource, quantity);
            return;
        }
    }

    Player player;
    player.id = player_id;
    map.players.push_back(player);

    client.write("ppo " + std::to_string(player_id) + "\n");
    client.write("pin " + std::to_string(player_id) + "\n");
    client.write("plv " + std::to_string(player_id) + "\n");
}

void Commands::playerResourceTake(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 3)
        return;
    int player_id = std::stoi(args[0]);
    std::string resource = args[1];
    int quantity = std::stoi(args[2]);

    for (auto &player: map.players) {
        if (player.id == player_id) {
            _removeItemsFromTile(map.tiles[player.position.x][player.position.y], scnMgr, resource, quantity);
            return;
        }
    }

    Player player;
    player.id = player_id;
    map.players.push_back(player);

    client.write("ppo " + std::to_string(player_id) + "\n");
    client.write("pin " + std::to_string(player_id) + "\n");
    client.write("plv " + std::to_string(player_id) + "\n");
}

void Commands::playerDeath(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int player_id = std::stoi(args[0]);

    for (auto &player: map.players) {
        if (player.id == player_id) {
            if (player.node)
                scnMgr->destroySceneNode(player.node);
            map.players.erase(std::remove(map.players.begin(), map.players.end(), player), map.players.end());
            return;
        }
    }
}

void Commands::playerEggLaid(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 4)
        return;
    int player_id = std::stoi(args[0]);
    int egg_id = std::stoi(args[1]);
    int x = std::stoi(args[2]);
    int y = std::stoi(args[3]);

    // TODO: Implement egg laying animation
}

void Commands::eggDeath(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int egg_id = std::stoi(args[1]);

    // TODO: Implement egg death animation
}

void Commands::eggHatching(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int egg_id = std::stoi(args[0]);

    // TODO: Implement egg hatching animation
}

void Commands::timeUnitRequest(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int time_unit = std::stoi(args[0]);

    // TODO: Implement time unit request
}

void Commands::timeUnitModification(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int time_unit = std::stoi(args[0]);

    // TODO: Implement time unit modification
}

void Commands::endGame(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    std::string winner = args[0];

    std::cout << "Game ended, team " << winner << " won!" << std::endl;
}

void Commands::unknownCommand(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::cout << "Unknown command: " << command << std::endl;
}

void Commands::commandParameters(std::string &command, Map &map, Ogre::SceneManager *scnMgr, Client &client) {
    std::cout << "Command parameters: " << command << std::endl;
}
