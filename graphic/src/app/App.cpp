/*
** EPITECH PROJECT, 2024
** App.cpp
** File description:
** App class
*/

#include "App.hpp"
#include <OgreCameraMan.h>
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

App::App() : OgreBites::ApplicationContext("Zappy"), _client(3001) {}

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

    for (int i = -5; i <= 5; i++) {
        for (int j = -5; j <= 5; j++) {
            Entity *cubeEntity = scnMgr->createEntity("Cube.mesh");
            SceneNode *node = scnMgr->getRootSceneNode()->createChildSceneNode();
            node->attachObject(cubeEntity);

            AxisAlignedBox aab = cubeEntity->getBoundingBox();
            Vector3 size = aab.getSize();
            node->setPosition(i * size.x, 0, j * size.z);
        }
    }

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
    if (_client.hasData()) {
        std::string command = _client.getCommandFromPendingBuffer();
        std::cout << "|" << command << "|" << std::endl;
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
