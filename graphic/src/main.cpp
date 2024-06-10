/*
** EPITECH PROJECT, 2024
** main.cpp
** File description:
** main class
*/

#include "app/App.hpp"

int main()
{
    App app;

    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
