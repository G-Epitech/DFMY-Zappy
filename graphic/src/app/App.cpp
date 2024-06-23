/*
** EPITECH PROJECT, 2024
** App.cpp
** File description:
** App class
*/

#include <iostream>
#include <OgreCameraMan.h>
#include <getopt.h>
#include "App.hpp"

using namespace Ogre;
using namespace OgreBites;

App::App() :
    OgreBites::ApplicationContext("Zappy"),
    _client(),
    trayMgr(nullptr),
    scnMgr(nullptr),
    _map(),
    _commands(),
    _options()
{
    this->_commands["msz"] = &Commands::mapSize;
    this->_commands["bct"] = &Commands::tileContent;
    this->_commands["tna"] = &Commands::teamsNames;
    this->_commands["pnw"] = &Commands::playerConnect;
    this->_commands["ppo"] = &Commands::playerPosition;
    this->_commands["plv"] = &Commands::playerLevel;
    this->_commands["pin"] = &Commands::playerInventory;
    this->_commands["pex"] = &Commands::playerEject;
    this->_commands["pbc"] = &Commands::broadcast;
    this->_commands["pic"] = &Commands::incantationStart;
    this->_commands["pie"] = &Commands::incantationEnd;
    this->_commands["pfk"] = &Commands::playerLayingEgg;
    this->_commands["pdr"] = &Commands::playerResourceDrop;
    this->_commands["pgt"] = &Commands::playerResourceTake;
    this->_commands["pdi"] = &Commands::playerDeath;
    this->_commands["enw"] = &Commands::playerEggLaid;
    this->_commands["edi"] = &Commands::eggDeath;
    this->_commands["ebo"] = &Commands::eggHatching;
    this->_commands["sgt"] = &Commands::timeUnitRequest;
    this->_commands["sst"] = &Commands::timeUnitModification;
    this->_commands["seg"] = &Commands::endGame;
    this->_commands["suc"] = &Commands::unknownCommand;
    this->_commands["sbp"] = &Commands::commandParameters;
}

void App::setup() {
    ApplicationContext::setup();
    addInputListener(this);

    Root *root = getRoot();
    root->loadPlugin("Codec_FreeImage");
    scnMgr = root->createSceneManager();
    scnMgr->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));

    _loadResources();
    _setupCamera();
    _setupMaterials();

    trayMgr = new TrayManager("TrayGUISystem", getRenderWindow());
    addInputListener(trayMgr);
    trayMgr->showFrameStats(TL_BOTTOMLEFT);
    trayMgr->showLogo(TL_BOTTOMRIGHT);
    trayMgr->hideCursor();
}

void App::_setupCamera() {
    Camera *cam = scnMgr->createCamera("myCam");
    cam->setAutoAspectRatio(true);
    cam->setNearClipDistance(0.1);
    cam->setFarClipDistance(1000);

    SceneNode *camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 20);
    camNode->lookAt(Vector3(0, 0, -1), Node::TS_PARENT);
    camNode->attachObject(cam);
    getRenderWindow()->addViewport(cam);

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

bool App::frameRenderingQueued(const Ogre::FrameEvent& evt) {
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

    for (auto &i : section) {
        for (auto &j : i.second) {
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

void App::_updateMap(std::string &command) {
    std::string commandName = command.substr(0, 3);
    if (this->_commands.find(commandName) != this->_commands.end()) {
        std::string params = command.substr(4);
        this->_commands[commandName](params, this->_map, this->scnMgr, this->_client);
    } else {
        std::cerr << "Unknown command: " << commandName << std::endl;
    }
}

void App::_updateBroadcastCircles(const Ogre::FrameEvent &evt) {
    for (auto &circle : _map.broadcastCircles) {
        if (circle.radius >= BROADCAST_CIRCLE_MAX_RADIUS) {
            if (circle.circle) {
                scnMgr->destroyManualObject(circle.circle);
                circle.circle = nullptr;
            }
            _map.broadcastCircles.erase(std::remove(_map.broadcastCircles.begin(), _map.broadcastCircles.end(), circle), _map.broadcastCircles.end());
            continue;
        }
        circle.radius += evt.timeSinceLastFrame * BROADCAST_SPEED;
        circle.circle->beginUpdate(0);
        for (int i = 0; i <= BROADCAST_CIRCLE_SEGMENTS; ++i)
        {
            float angle = Ogre::Math::TWO_PI * i / BROADCAST_CIRCLE_SEGMENTS;
            circle.circle->position(Ogre::Math::Cos(angle) * circle.radius, 0, Ogre::Math::Sin(angle) * circle.radius);
        }
        circle.circle->end();
    }
}

void App::_updateIncantationSpheres(const Ogre::FrameEvent &evt) {
    for (auto &sphere : _map.incantationSpheres) {
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

void App::_updateSphere(Ogre::ManualObject* obj, float radius, int rings, int segments)
{
    obj->clear();
    obj->begin("TransparentMaterial", RenderOperation::OT_TRIANGLE_LIST);

    float fDeltaRingAngle = (Math::PI / rings);
    float fDeltaSegAngle = (Math::TWO_PI / segments);
    unsigned short wVerticeIndex = 0;

    // Generate the group of rings for the sphere
    for (int ring = 0; ring <= rings; ring++)
    {
        float r0 = radius * sinf(ring * fDeltaRingAngle);
        float y0 = radius * cosf(ring * fDeltaRingAngle);

        // Generate the group of segments for the current ring
        for (int seg = 0; seg <= segments; seg++)
        {
            float x0 = r0 * sinf(seg * fDeltaSegAngle);
            float z0 = r0 * cosf(seg * fDeltaSegAngle);

            // Add one vertex to the strip which makes up the sphere
            obj->position(x0, y0, z0);
            obj->normal(Vector3(x0, y0, z0).normalisedCopy());
            obj->textureCoord((float)seg / (float)segments, (float)ring / (float)rings);

            if (ring != rings)
            {
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
