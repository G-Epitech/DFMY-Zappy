/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Commands
*/

#include <iostream>
#include "Commands.hpp"
#include "utils/String.hpp"
#include "constants/Tile.hpp"

std::vector<std::string> stonesNames = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

Commands::Commands(Client &client, Map &map, Ogre::SceneManager *scnMgr, OgreBites::TextBox *log,
                   OgreBites::Slider *timeSlider, bool &timeSliderChanged) : _client(client), _map(map),
                                                                             _scnMgr(scnMgr), _logs(log),
                                                                             _timeSlider(timeSlider),
                                                                             _timeSliderChanged(timeSliderChanged) {
    _commands["msz"] = [this](std::string &params) { mapSize(params); };
    _commands["bct"] = [this](std::string &params) { tileContent(params); };
    _commands["tna"] = [this](std::string &params) { teamsNames(params); };
    _commands["pnw"] = [this](std::string &params) { playerConnect(params); };
    _commands["ppo"] = [this](std::string &params) { playerPosition(params); };
    _commands["plv"] = [this](std::string &params) { playerLevel(params); };
    _commands["pin"] = [this](std::string &params) { playerInventory(params); };
    _commands["pex"] = [this](std::string &params) { playerEject(params); };
    _commands["pbc"] = [this](std::string &params) { broadcast(params); };
    _commands["pic"] = [this](std::string &params) { incantationStart(params); };
    _commands["pie"] = [this](std::string &params) { incantationEnd(params); };
    _commands["pfk"] = [this](std::string &params) { playerLayingEgg(params); };
    _commands["pdr"] = [this](std::string &params) { playerResourceDrop(params); };
    _commands["pgt"] = [this](std::string &params) { playerResourceTake(params); };
    _commands["pdi"] = [this](std::string &params) { playerDeath(params); };
    _commands["enw"] = [this](std::string &params) { playerEggLaid(params); };
    _commands["edi"] = [this](std::string &params) { eggDeath(params); };
    _commands["ebo"] = [this](std::string &params) { eggHatching(params); };
    _commands["sgt"] = [this](std::string &params) { timeUnitRequest(params); };
    _commands["sst"] = [this](std::string &params) { timeUnitModification(params); };
    _commands["seg"] = [this](std::string &params) { endGame(params); };
    _commands["suc"] = [this](std::string &params) { unknownCommand(params); };
    _commands["sbp"] = [this](std::string &params) { commandParameters(params); };
}

Commands::~Commands() = default;

void Commands::execute(std::string &command, std::string &params) {
    if (_commands.find(command) != _commands.end()) {
        _commands[command](params);
    } else {
        unknownCommand(command);
    }
}

void Commands::setScnMgr(Ogre::SceneManager *scnMgr) {
    _scnMgr = scnMgr;
}

void Commands::setLogs(OgreBites::TextBox *logs) {
    _logs = logs;
}

void Commands::setTimeSlider(OgreBites::Slider *timeSlider) {
    _timeSlider = timeSlider;
}

Circle Commands::_createBroadcastCircle(const Ogre::Vector3 &position) {
    Circle circle;
    circle.circle = _scnMgr->createManualObject();
    circle.node = _scnMgr->getRootSceneNode()->createChildSceneNode();
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

Sphere Commands::_createIncantationSphere(const Ogre::Vector3 &position) {
    Sphere sphere;
    sphere.sphere = _scnMgr->createManualObject();
    sphere.node = _scnMgr->getRootSceneNode()->createChildSceneNode();
    sphere.node->attachObject(sphere.sphere);
    sphere.node->setPosition(position);

    return sphere;
}

void Commands::_addLogMessage(const std::string &message) {
    if (!_logs)
        return;
    auto previousText = _logs->getText();
    // Cut previous message if it's too long
    if (previousText.size() > 1000) {
        previousText = previousText.substr(0, 1000);
    }
    _logs->setText(message + "\n" + previousText);
}

void Commands::mapSize(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 2)
        return;

    _map.width = std::stoi(args[0]);
    _map.height = std::stoi(args[1]);
    float posx = static_cast<float>(_map.width) / 2;
    float posy;
    float rotation;
    for (int i = 0; i < _map.width; i++) {
        std::vector<std::shared_ptr<Tile>> row;
        posy = static_cast<float>(_map.width) / 2;
        for (int j = 0; j < _map.height; j++) {
            Ogre::Entity *cubeEntity = _scnMgr->createEntity("Island.mesh");
            Ogre::SceneNode *node = _scnMgr->getRootSceneNode()->createChildSceneNode();

            node->attachObject(cubeEntity);

            Ogre::AxisAlignedBox aab = cubeEntity->getBoundingBox();
            Ogre::Vector3 size = aab.getSize();

            node->setPosition(posx * size.x, (-size.y / 2.0), posy * size.z);
            rotation = static_cast<float>(std::rand()) / RAND_MAX * 360;
            node->setOrientation(Ogre::Quaternion(Ogre::Degree(rotation), Ogre::Vector3::UNIT_Y));
            node->setScale(TILE_SCALE, TILE_SCALE, TILE_SCALE);

            auto tile = std::make_shared<Tile>(node);

            for (const auto &stonesName: stonesNames) {
                tile->items[stonesName] = {};
            }
            row.push_back(tile);
            posy = posy - 1 - MAP_TILE_Y_OFFSET;
        }

        _map.tiles.push_back(row);
        posx = posx - 1 - MAP_TILE_X_OFFSET;
    }
}

void Commands::tileContent(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

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

void Commands::teamsNames(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;

    for (const auto &arg: args) {
        _map.teams.addTeam(arg);
    }
}

void Commands::playerConnect(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 6)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    int orientation = std::stoi(args[3]);
    int level = std::stoi(args[4]);
    std::string team = args[5];

    if (x < 0 || x >= _map.width || y < 0 || y >= _map.height)
        return;

    for (const auto &player: _map.players) {
        if (player->getId() == id) {
            return;
        }
    }

    auto player = std::make_shared<Player>(id, team);
    player->orientation = orientation;
    player->level = level;
    player->position = {x, y};
    player->createEntity(_scnMgr, _map.teams, _map.tiles[x][y]->getNode());
    _map.players.push_back(player);

    _client.write("pin " + std::to_string(id) + "\n");

    if (!_map.selectedTeam.empty() && _map.selectedTeam != team) {
        player->node->setVisible(false);
    }
}

void Commands::playerPosition(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 4)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);
    int orientation = std::stoi(args[3]);
    if (x < 0 || x >= _map.width || y < 0 || y >= _map.height)
        return;
    for (auto &player: _map.players) {
        if (player->getId() == id) {
            player->position.x = x;
            player->position.y = y;
            player->orientation = orientation;
            player->node->setPosition(_map.tiles[x][y]->getNode()->getPosition().x, player->node->getPosition().y,
                                      _map.tiles[x][y]->getNode()->getPosition().z);
            if (!player->node)
                player->createEntity(_scnMgr, _map.teams, _map.tiles[x][y]->getNode());
            else
                player->updateEntitySize(_scnMgr, _map.teams, _map.tiles[x][y]->getNode());
            return;
        }
    }
}

void Commands::playerLevel(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 2)
        return;
    int id = std::stoi(args[0]);
    int level = std::stoi(args[1]);

    for (auto &player: _map.players) {
        if (player->getId() == id) {
            player->level = level;
            player->updateEntitySize(_scnMgr, _map.teams,
                                     _map.tiles[player->position.x][player->position.y]->getNode());
            return;
        }
    }
}

void Commands::playerInventory(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 10)
        return;
    int id = std::stoi(args[0]);
    int x = std::stoi(args[1]);
    int y = std::stoi(args[2]);

    if (x < 0 || x >= _map.width || y < 0 || y >= _map.height)
        return;

    for (auto &player: _map.players) {
        if (player->getId() == id) {
            player->addInventoryItem("food", std::stoi(args[3]));
            player->addInventoryItem("linemate", std::stoi(args[4]));
            player->addInventoryItem("deraumere", std::stoi(args[5]));
            player->addInventoryItem("sibur", std::stoi(args[6]));
            player->addInventoryItem("mendiane", std::stoi(args[7]));
            player->addInventoryItem("phiras", std::stoi(args[8]));
            player->addInventoryItem("thystame", std::stoi(args[9]));
            return;
        }
    }
}

void Commands::playerEject(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int id = std::stoi(args[0]);

    // TODO: Implement player ejection
    std::cout << "Player " << id << " have been ejected or eject others?" << std::endl;
}

void Commands::broadcast(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() < 2)
        return;
    int id = std::stoi(args[0]);
    std::string message = args[1];

    for (auto &player: _map.players) {
        if (player->getId() == id) {
            if (!_map.selectedTeam.empty() && _map.selectedTeam != player->getTeam()) {
                return;
            }

            Circle circle = _createBroadcastCircle(player->node->getPosition());
            _map.broadcastCircles.push_back(circle);
            _addLogMessage("Player " + std::to_string(id) + " broadcasted: " + message);
            return;
        }
    }
}

void Commands::incantationStart(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() < 3)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);
    int level = std::stoi(args[2]);

    // TODO: Implement incantation animation
    Sphere sphere = _createIncantationSphere(_map.tiles[x][y]->getNode()->getPosition());
    _map.incantationSpheres.push_back(sphere);
}

void Commands::incantationEnd(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() < 3)
        return;
    int x = std::stoi(args[0]);
    int y = std::stoi(args[1]);

    for (auto &sphere: _map.incantationSpheres) {
        if (sphere.node->getPosition() == _map.tiles[x][y]->getNode()->getPosition()) {
            _scnMgr->destroySceneNode(sphere.node);
            _map.incantationSpheres.erase(
                    std::remove(_map.incantationSpheres.begin(), _map.incantationSpheres.end(), sphere),
                    _map.incantationSpheres.end());
        }
    }

    for (auto &player: _map.players) {
        if (player->position.x == x && player->position.y == y) {
            std::string command = "plv " + std::to_string(player->getId()) + "\n";
            _client.write(command);
        }
    }
}

void Commands::playerLayingEgg(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int player_id = std::stoi(args[0]);

    // TODO: Implement egg laying animation
}

void Commands::playerResourceDrop(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 2)
        return;
    int player_id = std::stoi(args[0]);
    std::string resource;
    if (std::stoi(args[1]) == 0)
        resource = "food";
    else
        resource = stonesNames[std::stoi(args[1]) - 1];

    for (auto &player: _map.players) {
        if (player->getId() == player_id) {
            player->removeInventoryItem(resource, 1);
            _map.tiles[player->position.x][player->position.y]->addItemEntity(resource, 1, _scnMgr);
            return;
        }
    }
}

void Commands::playerResourceTake(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 2)
        return;
    int player_id = std::stoi(args[0]);
    std::string resource;
    if (std::stoi(args[1]) == 0)
        resource = "food";
    else
        resource = stonesNames[std::stoi(args[1]) - 1];

    for (auto &player: _map.players) {
        if (player->getId() == player_id) {
            player->addInventoryItem(resource, 1);
            _map.tiles[player->position.x][player->position.y]->removeItemEntity(resource, 1, _scnMgr);
            return;
        }
    }
}

void Commands::playerDeath(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int player_id = std::stoi(args[0]);

    for (auto &player: _map.players) {
        if (player->getId() == player_id) {
            if (player->node)
                _scnMgr->destroySceneNode(player->node);
            _map.players.erase(std::remove(_map.players.begin(), _map.players.end(), player), _map.players.end());
            return;
        }
    }
}

void Commands::playerEggLaid(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 4)
        return;
    int player_id = std::stoi(args[0]);
    int egg_id = std::stoi(args[1]);
    int x = std::stoi(args[2]);
    int y = std::stoi(args[3]);

    // TODO: Implement egg laying animation
}

void Commands::eggDeath(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int egg_id = std::stoi(args[1]);

    // TODO: Implement egg death animation
}

void Commands::eggHatching(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    int egg_id = std::stoi(args[0]);

    // TODO: Implement egg hatching animation
}

void Commands::timeUnitRequest(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1 || args[0] == "0")
        return;

    _map.timeUnit = std::stoi(args[0]);
    _timeSlider->setValue(_map.timeUnit);
    _timeSliderChanged = true;
}

void Commands::timeUnitModification(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1 || args[0] == "0")
        return;

    _map.timeUnit = std::stoi(args[0]);
    _timeSlider->setValue(_map.timeUnit);
    _timeSliderChanged = true;
}

void Commands::endGame(std::string &command) {
    std::vector<std::string> args = Utils::StringUtils::split(command, ' ');

    if (args.size() != 1)
        return;
    std::string winner = args[0];

    std::cout << "Game ended, team " << winner << " won!" << std::endl;
}

void Commands::unknownCommand(std::string &command) {
    std::cout << "Unknown command: " << command << std::endl;
}

void Commands::commandParameters(std::string &command) {
    std::cout << "Command parameters: " << command << std::endl;
}
