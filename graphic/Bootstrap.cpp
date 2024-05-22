/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main class
*/

#include "Ogre.h"
#include "OgreApplicationContext.h"

using namespace Ogre;

class KeyHandler : public OgreBites::InputListener {
    bool keyPressed(const OgreBites::KeyboardEvent &evt) override {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
            Ogre::Root::getSingleton().queueEndRendering();
        }
        return true;
    }
};

int main() {
    OgreBites::ApplicationContext ctx("OgreTutorialApp");
    ctx.initApp();

    Ogre::Root *root = ctx.getRoot();
    Ogre::SceneManager *scnMgr = root->createSceneManager();

    Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    Light *light = scnMgr->createLight("MainLight");
    SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(20, 80, 50);
    lightNode->attachObject(light);

    SceneNode *camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera *cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

    // and tell it to render into the main window
    ctx.getRenderWindow()->addViewport(cam);

    Ogre::ResourceGroupManager &rgm = Ogre::ResourceGroupManager::getSingleton();
    rgm.createResourceGroup("Bootstrap");
    rgm.addResourceLocation("../bin", "FileSystem", "Bootstrap");
    rgm.initialiseResourceGroup("Bootstrap");
    rgm.loadResourceGroup("Bootstrap");

    Entity *ogreEntity = scnMgr->createEntity("ogrehead.mesh");

    SceneNode *ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode->attachObject(ogreEntity);

    KeyHandler keyHandler;
    ctx.addInputListener(&keyHandler);

    ctx.getRoot()->startRendering();
    ctx.closeApp();
    return 0;
}
