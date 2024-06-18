/*
** EPITECH PROJECT, 2024
** App.cpp
** File description:
** App class
*/

#include <iostream>
#include <OgreCameraMan.h>
#include "App.hpp"
#include "commands/Commands.hpp"

using namespace Ogre;
using namespace OgreBites;

App::App() : OgreBites::ApplicationContext("Zappy"), _client(3001) {
    _client.write("mct\n");
    this->_commands["msz"] = &Commands::map_size;
    this->_commands["bct"] = &Commands::tile_content;
    this->_commands["tna"] = &Commands::teams_names;
    this->_commands["pnw"] = &Commands::player_connect;
    this->_commands["ppo"] = &Commands::player_position;
    this->_commands["plv"] = &Commands::player_level;
    this->_commands["pin"] = &Commands::player_inventory;
    this->_commands["pex"] = &Commands::player_eject;
    this->_commands["pbc"] = &Commands::broadcast;
    this->_commands["pic"] = &Commands::incantation_start;
    this->_commands["pie"] = &Commands::incantation_end;
    this->_commands["pfk"] = &Commands::player_laying_egg;
    this->_commands["pdr"] = &Commands::player_resource_drop;
    this->_commands["pgt"] = &Commands::player_resource_take;
    this->_commands["pdi"] = &Commands::player_death;
    this->_commands["enw"] = &Commands::player_egg_laid;
    this->_commands["edi"] = &Commands::egg_death;
    this->_commands["ebo"] = &Commands::egg_hatching;
    this->_commands["sgt"] = &Commands::time_unit_request;
    this->_commands["sst"] = &Commands::time_unit_modification;
    this->_commands["seg"] = &Commands::end_game;
    this->_commands["suc"] = &Commands::unknown_command;
    this->_commands["sbp"] = &Commands::command_parameters;
}

void App::setup() {
    ApplicationContext::setup();
    addInputListener(this);

    Root *root = getRoot();
    scnMgr = root->createSceneManager();

    _loadResources();

    scnMgr->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f)); // Soft white ambient light

    Camera *cam = scnMgr->createCamera("myCam");
    cam->setAutoAspectRatio(true);
    cam->setNearClipDistance(0.1);
    cam->setFarClipDistance(1000);

    SceneNode *camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 20);
    camNode->lookAt(Vector3(0, 0, -1), Node::TS_PARENT);
    camNode->attachObject(cam);

    getRenderWindow()->addViewport(cam);

    // for (int i = -5; i <= 5; i++) {
    //     for (int j = -5; j <= 5; j++) {
    //         Entity *cubeEntity = scnMgr->createEntity("Cube.mesh");
    //         SceneNode *node = scnMgr->getRootSceneNode()->createChildSceneNode();
    //         node->attachObject(cubeEntity);

    //         AxisAlignedBox aab = cubeEntity->getBoundingBox();
    //         Vector3 size = aab.getSize();
    //         node->setPosition(i * size.x, 0, j * size.z);
    //     }
    // }

    CameraMan *camMan = new CameraMan(camNode);
    camMan->setStyle(CS_ORBIT);
    addInputListener(camMan);

    TrayManager *trayMgr = new TrayManager("TrayGUISystem", getRenderWindow());
    addInputListener(trayMgr);
    trayMgr->showFrameStats(TL_BOTTOMLEFT);
    trayMgr->showLogo(TL_BOTTOMRIGHT);
    trayMgr->hideCursor();
}

bool App::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    for (auto &circle : _map.broadcastCircles) {
        if (circle.radius >= BROADCAST_CIRCLE_MAX_RADIUS) {
            if (circle.circle) {
                scnMgr->destroyManualObject(circle.circle);
                circle.circle = nullptr;
            }
            _map.broadcastCircles.erase(std::remove(_map.broadcastCircles.begin(), _map.broadcastCircles.end(), circle), _map.broadcastCircles.end());
            continue;
        }
        circle.radius += evt.timeSinceLastFrame * 3.0f; // Adjust the speed as needed
        circle.circle->beginUpdate(0);
        for (int i = 0; i <= BROADCAST_CIRCLE_SEGMENTS; ++i)
        {
            float angle = Ogre::Math::TWO_PI * i / BROADCAST_CIRCLE_SEGMENTS;
            circle.circle->position(Ogre::Math::Cos(angle) * circle.radius, 0, Ogre::Math::Sin(angle) * circle.radius);
        }
        circle.circle->end();
    }
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

    ConfigFile::SectionIterator section = cf.getSectionIterator();
    String typeName, archName;

    while (section.hasMoreElements()) {
        ConfigFile::SettingsMultiMap *settings = section.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
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

void App::_updateMap(std::string &command) {
    std::string commandName = command.substr(0, 3);
    if (this->_commands.find(commandName) != this->_commands.end()) {
        std::string params = command.substr(4);
        this->_commands[commandName](params, this->_map, this->scnMgr, this->_client);
    } else {
        std::cerr << "Unknown command: " << commandName << std::endl;
    }
}
