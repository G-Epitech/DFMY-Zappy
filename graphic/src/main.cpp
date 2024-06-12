/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main class
*/

#include "app/App.hpp"
#include <iostream>

int main(int ac, char **av) {
    for (int i = 0; i < ac; i++) {
        std::cout << av[i] << std::endl;
    }
    try {
        App app;
        app.initApp();
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
