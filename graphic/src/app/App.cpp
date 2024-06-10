/*
** EPITECH PROJECT, 2024
** App.cpp
** File description:
** App class
*/

#include "App.hpp"

using namespace Ogre;
using namespace OgreBites;

App::App() : OgreBites::ApplicationContext("ZappyGUI") {
}

void App::setup() {
    ApplicationContextBase::setup();
    addInputListener(this);

    Root *root = getRoot();
    sceneManager = root->createSceneManager();

    _loadResources();

    trayManager = new TrayManager("TrayGUISystem", getRenderWindow());
    addInputListener(trayManager);
    trayManager->showFrameStats(TL_BOTTOMLEFT);
    trayManager->showLogo(TL_BOTTOMRIGHT);
    trayManager->hideCursor();
}

void App::_loadResources() {
    Ogre::ResourceGroupManager &rgm = Ogre::ResourceGroupManager::getSingleton();

    rgm.createResourceGroup("Main");
    //rgm.addResourceLocation("../bin", "FileSystem", "Main");
    rgm.initialiseResourceGroup("Main");
    rgm.loadResourceGroup("Main");
}

bool App::keyPressed(const KeyboardEvent &evt) {
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }
    return true;
}
