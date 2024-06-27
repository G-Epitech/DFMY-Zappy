/*
** EPITECH PROJECT, 2024
** App.cpp
** File description:
** App class
*/

#include <iostream>
#include <OgreCameraMan.h>
#include <OgreViewport.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>
#include <OgreBorderPanelOverlayElement.h>
#include <getopt.h>
#include "App.hpp"
#include "commands/CommandFactory.hpp"

using namespace Ogre;
using namespace OgreBites;

App::App() :
        OgreBites::ApplicationContext("Zappy"),
        _client(),
        trayMgr(nullptr),
        _scnMgr(nullptr),
        _map(),
        _commands(_client, _map, nullptr, nullptr, nullptr, _timeSliderChanged),
        _options(),
        _infosLabel(nullptr),
        _infosPanel(nullptr),
        _teamLabel(nullptr),
        _teamPanel(nullptr),
        _timeSliderChanged(false) {}

void App::setup() {
    ApplicationContext::setup();
    addInputListener(this);
    Root *root = getRoot();

    _scnMgr = root->createSceneManager();
    _scnMgr->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));
    _raySceneQuery = _scnMgr->createRayQuery(Ogre::Ray());

    _commands.setScnMgr(_scnMgr);
    _scnMgr->setSkyBox(true, "skybox", 300, true);

    _loadResources();
    _setupCamera();
    _setupMaterials();
    _setupUI();
    _setupLights();
    _setupAudio();
}

void App::_setupCamera() {
    _camera = _scnMgr->createCamera("myCam");
    _camera->setAutoAspectRatio(true);
    _camera->setNearClipDistance(0.1);
    _camera->setFarClipDistance(1000);

    SceneNode *camNode = _scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(20, -20, -20);
    camNode->lookAt(Vector3(0, 0, -1), Node::TS_PARENT);
    camNode->attachObject(_camera);
    getRenderWindow()->addViewport(_camera);

    auto *camMan = new CameraMan(camNode);
    camMan->setStyle(CS_ORBIT);
    addInputListener(camMan);
}

void App::_setupMaterials() {
    MaterialPtr material = MaterialManager::getSingleton().create("TransparentMaterial",
                                                                  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    material->setDiffuse(1, 1, 1, 0.5);
    material->setAmbient(0, 0.65, 1);
    material->setSceneBlending(SBT_TRANSPARENT_ALPHA);
    material->setDepthWriteEnabled(false);
}

void App::_setupUI() {
    _scnMgr->addRenderQueueListener(getOverlaySystem());

    trayMgr = new TrayManager("TrayGUISystem", getRenderWindow());
    addInputListener(trayMgr);
    trayMgr->setListener(this);
    trayMgr->showFrameStats(TL_BOTTOMRIGHT);
    trayMgr->hideCursor();

    _setupButtons();
    _setupDropdowns();
    _setupInformations();
    _setupMapStats();
    _setupLogs();
    _setupSliders();
    _setupCommands();
}

void App::_setupInformations() {
    Ogre::OverlayManager &overlayMgr = Ogre::OverlayManager::getSingleton();
    Ogre::OverlayContainer *panel = static_cast<Ogre::OverlayContainer *>(overlayMgr.createOverlayElement("Panel",
                                                                                                          "MyPanel"));
    Ogre::Real width = 200;
    Ogre::Real height = 158.7;

    panel->setMetricsMode(Ogre::GMM_PIXELS);
    panel->setPosition(0, 50);
    panel->setDimensions(width, height);
    panel->setMaterialName("gepitech");

    trayMgr->getTrayContainer(TL_TOPLEFT)->addChild(panel);
    trayMgr->createButton(TL_TOPLEFT, "infos", "Informations", 185);
}

void App::_setupMapStats() {
    Ogre::StringVector stats;

    stats.push_back("Width");
    stats.push_back("Height");
    stats.push_back("Time unit");
    stats.push_back("Players");
    stats.push_back("Items");
    stats.push_back("Broadcasts");

    _mapLabel = trayMgr->createLabel(TL_NONE, "Map/StatsLabel", "Infos map", 180);
    _mapLabel->_assignListener(this);
    _mapPanel = trayMgr->createParamsPanel(TL_NONE, "Map/StatsPanel", 180, stats);

    trayMgr->moveWidgetToTray(_mapLabel, TL_TOPRIGHT, -1);
    trayMgr->moveWidgetToTray(_mapPanel, TL_TOPRIGHT, trayMgr->locateWidgetInTray(_mapLabel) + 1);
}

void App::_setupButtons() {
    _pauseButton = trayMgr->createButton(TL_BOTTOM, "Pause", "Pause", 200);
}

void App::_setupDropdowns() {
    _teamsDropdown = trayMgr->createThickSelectMenu(TL_BOTTOMLEFT, "Teams", "Teams", 300, 200);
    _teamsDropdown->addItem("All teams");
    _teamsDropdown->selectItem(0);

    // TODO: Add teams from the server
    _teamsDropdown->addItem("team1");
    _teamsDropdown->addItem("team2");
}

void App::_setupLights() {
    auto sunLight = _scnMgr->createLight("SunLight");
    sunLight->setType(Light::LT_DIRECTIONAL);
    sunLight->setPowerScale(0.1f);
    sunLight->setAttenuation(100, 10, 10, 100);
    sunLight->setSourceSize(2.0f, 2.0f);
    sunLight->setCastShadows(true);
    sunLight->setDiffuseColour(ColourValue(1.0f, 1.0f, 1.0f));
    sunLight->setSpecularColour(ColourValue(1.0f, 1.0f, 1.0f));

    auto sunNode = _scnMgr->getRootSceneNode()->createChildSceneNode();
    sunNode->attachObject(sunLight);
    sunNode->setDirection(Vector3(1, -1, 0));
    sunNode->setPosition(-200, -200, 400);
}

void App::_setupAudio() {
    if (!_background_music.openFromFile("audio/background_music.wav")) {
        std::cerr << "Failed to load music file!" << std::endl;
    } else {
        _background_music.play();
    }
}

void App::_setupLogs() {
    _logs = trayMgr->createTextBox(TL_BOTTOMLEFT, "Logs", "Logs", 300, 200);
    _commands.setLogs(_logs);
}

void App::_setupSliders() {
    _timeSlider = trayMgr->createLongSlider(TL_BOTTOMLEFT, "TimeSlider", "Time", 150, 100, 1, 500, 100);
    _commands.setTimeSlider(_timeSlider);
}

void App::_setupCommands() {
    CommandFactory commandFactory(_client, _map, _timeSliderChanged);
    std::vector<std::string> commands = {
        "msz",
        "bct",
        "tna",
        "pnw",
        "ppo",
        "plv",
        "pin",
        "pex",
        "pbc",
        "pic",
        "pie",
        "pfk",
        "pdr",
        "pgt"
    };

    for (const auto &command: commands) {
        _commandsMap[command] = commandFactory.createCommand(command);
    }

    for (auto &command: _commandsMap) {
        if (command.second) {
            command.second->setLogs(_logs);
            command.second->setScnMgr(_scnMgr);
            command.second->setSlider(_timeSlider);
        }
    }
}

bool App::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    trayMgr->frameRendered(evt);
    _updateBroadcastCircles(evt);
    _updateIncantationSpheres(evt);
    _updateMapStats(evt);
    return true;
}

void App::_updateMapStats(const Ogre::FrameEvent &evt) {
    // Update map stats every 1 second with _lastStatsRefresh
    _lastStatsRefresh += evt.timeSinceLastFrame;
    if (_lastStatsRefresh < 1) {
        return;
    }

    _lastStatsRefresh = 0;
    if (_mapLabel && _mapPanel) {
        Ogre::StringVector values;

        values.push_back(std::to_string(_map.width));
        values.push_back(std::to_string(_map.height));
        values.push_back(std::to_string(_map.timeUnit));
        values.push_back(std::to_string(_map.players.size()));

        size_t numberOfItems = 0;
        for (auto &row: _map.tiles) {
            for (auto &tile: row) {
                for (auto &item: tile->items) {
                    numberOfItems += item.second.size();
                }
            }
        }
        values.push_back(std::to_string(numberOfItems));

        size_t numberOfBroadcasts = 0;
        for (auto &circle: _map.broadcastCircles) {
            if (circle.circle->isVisible()) {
                numberOfBroadcasts++;
            }
        }

        values.push_back(std::to_string(numberOfBroadcasts));

        _mapPanel->setAllParamValues(values);
    }

    if (_teamLabel && _teamPanel) {
        Ogre::StringVector values;

        int nbPlayers = 0;
        int maxLevel = 0;
        int nbMaxLevel = 0;
        std::vector<int> stones = {0, 0, 0, 0, 0, 0, 0};

        for (auto &player: _map.players) {
            if (player->getTeam() == _map.selectedTeam) {
                if (player->level > maxLevel) {
                    maxLevel = player->level;
                    nbMaxLevel = 1;
                } else if (player->level == maxLevel) {
                    nbMaxLevel++;
                }
                nbPlayers++;

                stones[0] += player->getItemQuantity("food");
                stones[1] += player->getItemQuantity("linemate");
                stones[2] += player->getItemQuantity("deraumere");
                stones[3] += player->getItemQuantity("sibur");
                stones[4] += player->getItemQuantity("mendiane");
                stones[5] += player->getItemQuantity("phiras");
                stones[6] += player->getItemQuantity("thystame");
            }
        }

        values.push_back(std::to_string(nbPlayers));
        values.push_back(std::to_string(maxLevel) + " (" + std::to_string(nbMaxLevel) + "p)");

        for (auto &stone: stones) {
            values.push_back(std::to_string(stone));
        }

        _teamPanel->setAllParamValues(values);
    }
}

bool App::frameEnded(const Ogre::FrameEvent &evt) {
    _client.poll();
    if (_client.hasData()) {
        std::string command = _client.getCommandFromPendingBuffer();

        while (!command.empty()) {
            _updateMap(command);
            command = _client.getCommandFromPendingBuffer();
        }
    }
    return true;
}

void App::_loadResources() {
    Ogre::ResourceGroupManager &rgm = Ogre::ResourceGroupManager::getSingleton();

    if (!rgm.resourceGroupExists("Main"))
        rgm.createResourceGroup("Main");

    ConfigFile cf;
    cf.load("resources.cfg");
    ConfigFile::SettingsBySection_ section = cf.getSettingsBySection();
    String typeName, archName;

    for (auto &i: section) {
        for (auto &j: i.second) {
            typeName = j.first;
            archName = j.second;
            rgm.addResourceLocation(archName, typeName, "Main");
        }
    }
    rgm.initialiseResourceGroup("Main");
    rgm.loadResourceGroup("Main");
}

bool App::keyPressed(const KeyboardEvent &evt) {
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }
    return true;
}

void App::buttonHit(OgreBites::Button *b) {
    if (b->getName() == "Pause") {
        if (_pauseButton->getCaption() == "Resume") {
            _pauseButton->setCaption("Pause");
            _client.write("sst " + std::to_string((int)_timeSlider->getValue()) + "\n");
        } else {
            _pauseButton->setCaption("Resume");
            _client.write("sst 0\n");
        }
    }
    if (b->getName() == "infos") {
        trayMgr->showOkDialog("Informations", "This is a Zappy GUI made by the G-Epitech team.\n\n"
                                              "You can use the dropdown to select a team and see only its players.\n"
                                              "You can also pause the game by clicking on the Pause button.\n"
                                              "Enjoy the game!");
        trayMgr->hideCursor();
    }
}

void App::itemSelected(OgreBites::SelectMenu *menu) {
    if (menu->getName() == "Teams") {
        if (_teamLabel && _teamPanel) {
            trayMgr->destroyWidget(_teamLabel);
            trayMgr->destroyWidget(_teamPanel);
            _teamLabel = nullptr;
            _teamPanel = nullptr;
        }

        auto selectedTeam = menu->getSelectedItem();
        if (selectedTeam == "All teams") {
            for (auto &player: _map.players) {
                player->node->setVisible(true);
            }
            _map.selectedTeam = "";
        } else {
            int nbPlayers = 0;

            _map.selectedTeam = selectedTeam;
            for (auto &player: _map.players) {
                if (player->getTeam() == selectedTeam) {
                    nbPlayers++;
                    player->node->setVisible(true);
                } else {
                    player->node->setVisible(false);
                }
            }

            Ogre::StringVector stats;
            stats.push_back("Players");
            stats.push_back("Max level");

            stats.push_back("Food");
            stats.push_back("Linemate");
            stats.push_back("Deraumere");
            stats.push_back("Sibur");
            stats.push_back("Mendiane");
            stats.push_back("Phiras");
            stats.push_back("Thystame");

            _teamLabel = trayMgr->createLabel(TL_NONE, "Team/StatsLabel", selectedTeam, 180);
            _teamPanel = trayMgr->createParamsPanel(TL_NONE, "Team/StatsPanel", 180, stats);

            trayMgr->moveWidgetToTray(_teamLabel, TL_TOPRIGHT);
            trayMgr->moveWidgetToTray(_teamPanel, TL_TOPRIGHT);
        }
    }
}

bool App::_isBroadcastNode(Ogre::Node *node) {
    for (auto &circle: _map.broadcastCircles) {
        if (circle.node == node) {
            return true;
        }
    }
    return false;
}

bool App::mousePressed(const MouseButtonEvent &evt) {
    if (evt.button == OgreBites::BUTTON_LEFT) {
        // Convert to ray
        Ogre::Ray ray = this->_getMouseRay(evt);

        // Execute ray query
        _raySceneQuery->setRay(ray);
        _raySceneQuery->setSortByDistance(true);

        Ogre::RaySceneQueryResult &result = _raySceneQuery->execute();
        for (auto it = result.begin(); it != result.end(); ++it) {
            if (it->movable) {
                Ogre::MovableObject *object = it->movable;
                Ogre::Node *node = object->getParentSceneNode();

                if (_isBroadcastNode(node)) {
                    continue;
                }

                _handleObjectSelection(node);
                break;
            }
        }
    }
    return true;
}

void App::sliderMoved(OgreBites::Slider *slider) {
    if (slider->getName() == "TimeSlider") {
        try {
            if (!_timeSliderChanged) {
                _client.write("sst " + std::to_string((int)slider->getValue()) + "\n");
            } else {
                _timeSliderChanged = false;
            }
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

void App::_handleObjectSelection(Ogre::Node *node) {
    Vector2 position(0, 0);

    if (_infosLabel && _infosPanel) {
        trayMgr->destroyWidget(_infosLabel);
        trayMgr->destroyWidget(_infosPanel);
        _infosLabel = nullptr;
        _infosPanel = nullptr;
    }

    // Tiles management
    for (auto &row: _map.tiles) {
        for (auto &tile: row) {
            if (tile->getNode() == node) {
                Ogre::StringVector stats;
                Ogre::StringVector values;

                stats.push_back("Position");
                values.push_back("x:" + std::to_string(static_cast<int>(position.x)) + ", y:" +
                                 std::to_string(static_cast<int>(position.y)));
                std::for_each(tile->items.begin(), tile->items.end(), [&stats, &values](const auto &item) {
                    stats.push_back(item.first);
                    values.push_back(std::to_string(item.second.size()));
                });

                _infosLabel = trayMgr->createLabel(TL_NONE, "Infos/StatsLabel", "Infos tile", 180);
                _infosLabel->_assignListener(this);
                _infosPanel = trayMgr->createParamsPanel(TL_NONE, "Infos/StatsPanel", 180, stats);
                _infosPanel->setAllParamValues(values);

                trayMgr->moveWidgetToTray(_infosLabel, TL_TOPRIGHT, trayMgr->locateWidgetInTray(_mapPanel) + 1);
                trayMgr->moveWidgetToTray(_infosPanel, TL_TOPRIGHT, trayMgr->locateWidgetInTray(_infosLabel) + 1);

                return;
            }
            position.x++;
        }
        position.y++;
        position.x = 0;
    }

    // Player management
    for (auto &player: _map.players) {
        if (player->node == node) {
            Ogre::StringVector stats;
            Ogre::StringVector values;

            stats.emplace_back("Position");
            values.push_back("x:" + std::to_string(static_cast<int>(player->position.x)) + ", y:" +
                             std::to_string(static_cast<int>(player->position.y)));

            stats.emplace_back("Team");
            values.push_back(player->getTeam());

            stats.emplace_back("Level");
            values.push_back(std::to_string(player->level));

            stats.emplace_back("Inventory");
            values.emplace_back("");

            stats.emplace_back("Food");
            values.push_back(std::to_string(player->getItemQuantity("food")));

            stats.emplace_back("Linemate");
            values.push_back(std::to_string(player->getItemQuantity("linemate")));

            stats.emplace_back("Deraumere");
            values.push_back(std::to_string(player->getItemQuantity("deraumere")));

            stats.emplace_back("Sibur");
            values.push_back(std::to_string(player->getItemQuantity("sibur")));

            stats.emplace_back("Mendiane");
            values.push_back(std::to_string(player->getItemQuantity("mendiane")));

            stats.emplace_back("Phiras");
            values.push_back(std::to_string(player->getItemQuantity("phiras")));

            stats.emplace_back("Thystame");
            values.push_back(std::to_string(player->getItemQuantity("thystame")));

            /*
            stats.emplace_back("Stones");
            values.emplace_back(std::to_string(_getPlayerStonesNumber(player)));
             */

            _infosLabel = trayMgr->createLabel(TL_NONE, "Infos/PlayerLabel", "Infos player", 180);
            _infosLabel->_assignListener(this);
            _infosPanel = trayMgr->createParamsPanel(TL_NONE, "Infos/PlayerPanel", 180, stats);
            _infosPanel->setAllParamValues(values);

            trayMgr->moveWidgetToTray(_infosLabel, TL_TOPRIGHT, -1);
            trayMgr->moveWidgetToTray(_infosPanel, TL_TOPRIGHT, trayMgr->locateWidgetInTray(_infosLabel) + 1);

            return;
        }
    }
}

Ogre::Ray App::_getMouseRay(const OgreBites::MouseButtonEvent &evt) {
    float mouseX = static_cast<float>(evt.x) / getRenderWindow()->getWidth();
    float mouseY = static_cast<float>(evt.y) / getRenderWindow()->getHeight();

    return _camera->getCameraToViewportRay(mouseX, mouseY);
}

void App::_updateMap(std::string &command) {
    if (command.length() < 3)
        return;

    std::string commandName = command.substr(0, 3);
    std::string params;

    if (command.length() > 3) {
        params = command.substr(4);
    }

    try {
        for (auto &command: _commandsMap) {
            if (command.first == commandName) {
                command.second->execute(params);
                break;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] On command " << commandName << " with paramters " << params << ": " << e.what() << '\n';
    }
}

void App::_updateBroadcastCircles(const Ogre::FrameEvent &evt) {
    for (auto &circle: _map.broadcastCircles) {
        if (circle.radius >= BROADCAST_CIRCLE_MAX_RADIUS) {
            circle.node->setVisible(false);
        }
        circle.radius += evt.timeSinceLastFrame * BROADCAST_SPEED;
        circle.circle->beginUpdate(0);
        for (int i = 0; i <= BROADCAST_CIRCLE_SEGMENTS; ++i) {
            float angle = Ogre::Math::TWO_PI * i / BROADCAST_CIRCLE_SEGMENTS;
            circle.circle->position(Ogre::Math::Cos(angle) * circle.radius, 0, Ogre::Math::Sin(angle) * circle.radius);
        }
        circle.circle->end();
    }
}

void App::_updateIncantationSpheres(const Ogre::FrameEvent &evt) {
    for (auto &sphere: _map.incantationSpheres) {
        if (sphere.isGrowing) {
            sphere.radius += evt.timeSinceLastFrame * INCANTATION_SPHERE_SPEED;
            if (sphere.radius >= INCANTATION_SPHERE_MAX_RADIUS) {
                sphere.isGrowing = false;
            }
        } else {
            sphere.radius -= evt.timeSinceLastFrame * INCANTATION_SPHERE_SPEED;
            if (sphere.radius <= INCANTATION_SPHERE_RADIUS) {
                sphere.isGrowing = true;
            }
        }
        _updateSphere(sphere.sphere, sphere.radius);
    }
}

void App::_updateSphere(Ogre::ManualObject *obj, float radius, int rings, int segments) {
    obj->clear();
    obj->begin("TransparentMaterial", RenderOperation::OT_TRIANGLE_LIST);

    float fDeltaRingAngle = (Math::PI / rings);
    float fDeltaSegAngle = (Math::TWO_PI / segments);
    unsigned short wVerticeIndex = 0;

    // Generate the group of rings for the sphere
    for (int ring = 0; ring <= rings; ring++) {
        float r0 = radius * sinf(ring * fDeltaRingAngle);
        float y0 = radius * cosf(ring * fDeltaRingAngle);

        // Generate the group of segments for the current ring
        for (int seg = 0; seg <= segments; seg++) {
            float x0 = r0 * sinf(seg * fDeltaSegAngle);
            float z0 = r0 * cosf(seg * fDeltaSegAngle);

            // Add one vertex to the strip which makes up the sphere
            obj->position(x0, y0, z0);
            obj->normal(Vector3(x0, y0, z0).normalisedCopy());
            obj->textureCoord((float) seg / (float) segments, (float) ring / (float) rings);

            if (ring != rings) {
                // each vertex (except the last) has six indices pointing to it
                obj->index(wVerticeIndex + segments + 1);
                obj->index(wVerticeIndex);
                obj->index(wVerticeIndex + segments);
                obj->index(wVerticeIndex + segments + 1);
                obj->index(wVerticeIndex + 1);
                obj->index(wVerticeIndex);
                wVerticeIndex++;
            }
        }
    }

    obj->end();
}

void App::_printUsage() noexcept {
    std::cout << "USAGE: ./zappy_gui -p port -h host" << std::endl;
}

bool App::parseOptions(int argc, char **argv) {
    int opt;

    if (argc != 5) {
        App::_printUsage();
        return false;
    }
    while ((opt = getopt(argc, argv, "p:h:")) != -1) {
        switch (opt) {
            case 'p':
                _options.port = static_cast<int>(std::strtol(optarg, nullptr, 10));
                break;
            case 'h':
                _options.host = optarg;
                break;
            default:
                break;
        }
    }
    return true;
}

bool App::establishConnection() {
    return _client.establishConnection(_options.host, _options.port);
}
