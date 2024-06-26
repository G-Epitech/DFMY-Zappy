/*
** EPITECH PROJECT, 2024
** App.hpp
** File description:
** App class
*/

/** @defgroup graphic_app Graphic App Module
 *  Main graphic application module
 *  @{
 */


#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreTrays.h>
#include <SFML/Audio.hpp>
#include "client/Client.hpp"
#include "types/Map.hpp"
#include "commands/Commands.hpp"

class App : public OgreBites::ApplicationContext, public OgreBites::InputListener, public OgreBites::TrayListener {
public:

    // @brief Options of the application
    typedef struct Options {
        // @brief Host of the server
        std::string host;
        // @brief Port of the server
        int port;
    } Options;

    /**
     * @brief Construct a new App object
     */
    App();

    /**
     * @brief Setup the application
     */
    void setup() override;

    /**
     * @brief Parse the cli arguments
     * @param argc Parameter count
     * @param argv Parameter values
     * @return true if the options are valid
     */
    bool parseOptions(int ac, char **av);

    /**
     * @brief Establish a connection to the server
     * @return true if the connection was successful
     */
    bool establishConnection();

    /**
     * @brief Key pressed event
     * @param evt Keyboard event
     * @return true if the event was handled
     */
    bool keyPressed(const OgreBites::KeyboardEvent &evt) override;

    /**
     * @brief Frame rendering queued event
     * @param evt Frame event
     * @return true if the event was handled
     */
    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;

    /**
     * @brief Frame ended event
     * @param evt Frame event
     * @return true if the event was handled
     */
    bool frameEnded(const Ogre::FrameEvent &evt) override;

    /**
     * @brief Button hit event
     * @param b Button that was hit
     */
    void buttonHit(OgreBites::Button *b) override;

    /**
     * @brief Select menu selection changed event
     * @param menu Select menu that was changed
     */
    void itemSelected(OgreBites::SelectMenu *menu) override;

    /**
     * @brief Mouse pressed event
     * @param evt Mouse button event
     * @return true if the event was handled
     */
    bool mousePressed(const OgreBites::MouseButtonEvent &evt) override;

private:
    /// @brief Client object used to communicate with the server
    Client _client;

    /// @brief Tray manager used to display GUI elements
    OgreBites::TrayManager *trayMgr;

    /// @brief Scene manager used to manage the scene
    Ogre::SceneManager *_scnMgr;

    /// @brief Map of the game with all the tiles, players...
    Map _map;

    /// @brief Commands object used to execute commands
    Commands _commands;

    /// @brief Options of the application
    Options _options;

    /// @brief Button used to pause the game
    OgreBites::Button* _pauseButton;

    /// @brief Dropdown used to select the team
    OgreBites::SelectMenu* _teamsDropdown;

    /// @brief Ray scene query used to detect the tile under the mouse
    Ogre::RaySceneQuery* _raySceneQuery;

    /// @brief Camera used to display the scene
    Ogre::Camera* _camera;

    /// @brief Background music of the application
    sf::Music _background_music;

    OgreBites::TextBox* _logs;

    /**
     * @brief Load resources of the application
     */
    static void _loadResources();

    /**
     * @brief Setup the camera
     */
    void _setupCamera();

    /**
     * @brief Setup the materials of the application
     */
    void _setupMaterials();

    /**
     * @brief Setup the UI of the application
     */
    void _setupUI();

    /**
     * @brief Setup the buttons of the application
     */
    void _setupButtons();

    /**
     * @brief Setup the dropdowns of the application
     */
    void _setupDropdowns();

    /**
     * @brief Setup the informations of the application
     */
    void _setupInformations();

    /**
     * @brief Setup the lights of the application
     */
    void _setupLights();

    /**
     * @brief Setup the audio of the application
     */
    void _setupAudio();

    /**
     * @brief Setup the logs of the application
     */
    void _setupLogs();

    /**
     * @brief Update the map
     * @param command Command received from the server
     */
    void _updateMap(std::string &command);

    /**
     * @brief Update the broadcast circles
     * @param evt Frame event
     */
    void _updateBroadcastCircles(const Ogre::FrameEvent &evt);

    /**
     * @brief Update the incantation spheres
     * @param evt Frame event
     */
    void _updateIncantationSpheres(const Ogre::FrameEvent &evt);

    /**
     * @brief Update the sphere
     * @param obj Manual object
     * @param radius Radius of the sphere
     * @param rings Number of rings
     * @param segments Number of segments
     */
    void _updateSphere(Ogre::ManualObject* obj, float radius, int rings = BROADCAST_CIRCLE_SEGMENTS, int segments = BROADCAST_CIRCLE_SEGMENTS);

    /**
     * @brief Print the usage of the application
     */
    static void _printUsage() noexcept;

    Ogre::Ray _getMouseRay(const OgreBites::MouseButtonEvent &evt);

    /**
     * @brief Handle the object selection
     * @param node Node of the object
     */
    void _handleObjectSelection(Ogre::Node *node);
};
