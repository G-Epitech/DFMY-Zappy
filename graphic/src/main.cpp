/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main class
*/

#include <iostream>
#include "app/App.hpp"
#include "../client/Client.hpp"

int main(int argc, char **argv)
{
    try {
        App app;

        if (!app.parseOptions(argc, argv))
            return 84;
        app.initApp();
        if (!app.establishConnection())
            return 84;
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const Ogre::Exception &e) {
        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "An exception has occurred: " << e.what() << std::endl;
    }
    return 0;
}
