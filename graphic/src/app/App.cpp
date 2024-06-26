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

using namespace Ogre;
using namespace OgreBites;

App::App() :
        OgreBites::ApplicationContext("Zappy"),
        _client(),
        trayMgr(nullptr),
        _scnMgr(nullptr),
        _map(),
        _commands(_client, _map, nullptr, nullptr),
        _options(),
        _infosLabel(nullptr),
        _infosPanel(nullptr) {}

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
    _setupLogs();
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

    // Ogre::Overlay *overlay = overlayMgr.create("MyOverlay");
    // overlay->add2D(panel);
    // overlay->show();

    trayMgr->createButton(TL_TOPLEFT, "infos", "Informations", 185);
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
    _scnMgr->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));

    auto sunLight = _scnMgr->createLight("SunLight");
    sunLight->setType(Light::LT_DIRECTIONAL);
    sunLight->setDiffuseColour(ColourValue(0.4, 0, 0));
    sunLight->setSpecularColour(ColourValue(0.4, 0, 0));

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

bool App::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    trayMgr->frameRendered(evt);
    _updateBroadcastCircles(evt);
    _updateIncantationSpheres(evt);
    return true;
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
            _client.write("sst 100\n");
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
        auto selectedTeam = menu->getSelectedItem();
        if (selectedTeam == "All teams") {
            for (auto &player: _map.players) {
                player.node->setVisible(true);
            }
        } else {
            for (auto &player: _map.players) {
                if (player.team == selectedTeam) {
                    player.node->setVisible(true);
                } else {
                    player.node->setVisible(false);
                }
            }
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
            if (tile.node == node) {
                Ogre::StringVector stats;
                Ogre::StringVector values;

                stats.push_back("Position");
                values.push_back("x:" + std::to_string(static_cast<int>(position.x)) + ", y:" +
                                 std::to_string(static_cast<int>(position.y)));
                std::for_each(tile.items.begin(), tile.items.end(), [&stats, &values](const auto &item) {
                    stats.push_back(item.first);
                    values.push_back(std::to_string(item.second.size()));
                });

                _infosLabel = trayMgr->createLabel(TL_NONE, "Infos/StatsLabel", "Infos tile", 180);
                _infosLabel->_assignListener(this);
                _infosPanel = trayMgr->createParamsPanel(TL_NONE, "Infos/StatsPanel", 180, stats);
                _infosPanel->setAllParamValues(values);

                trayMgr->moveWidgetToTray(_infosLabel, TL_TOPRIGHT, -1);
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
        if (player.node == node) {
            Ogre::StringVector stats;
            Ogre::StringVector values;

            stats.emplace_back("Position");
            values.push_back("x:" + std::to_string(static_cast<int>(player.position.x)) + ", y:" +
                             std::to_string(static_cast<int>(player.position.y)));

            stats.emplace_back("Team");
            values.push_back(player.team);

            stats.emplace_back("Level");
            values.push_back(std::to_string(player.level));

            stats.emplace_back("Inventory");
            values.emplace_back("");

            stats.emplace_back("Food");
            values.push_back(std::to_string(player.inventory.food));

            stats.emplace_back("Stones");
            values.emplace_back(std::to_string(_getPlayerStonesNumber(player)));

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

int App::_getPlayerStonesNumber(const Player &player) {
    return player.inventory.linemate + player.inventory.deraumere + player.inventory.sibur +
           player.inventory.mendiane + player.inventory.phiras + player.inventory.thystame;
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
        _commands.execute(commandName, params);
    } catch(const std::exception& e) {
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
