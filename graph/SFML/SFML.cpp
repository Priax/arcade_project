/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** SFML
*/

#include "../SFML.hpp"

arcade::SFML::SFML()
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade", sf::Style::Close | sf::Style::Resize);
    // _window.setFramerateLimit(30);
}

void arcade::SFML::setFont()
{
    sf::Font textFont = sf::Font();
    const std::string path("./assets/SFML/Tag.ttf");
    textFont.loadFromFile(path);
    _textFont = sf::Font(textFont);
}

void arcade::SFML::displayWindow(arcade::GameState &gs)
{
    switch (gs.getState()) {
    case ARCADE_MENU:
        if (_isCreated == false || _status != ARCADE_MENU) {
            _isCreated = true;
            _status = ARCADE_MENU;
            setMenuAssets(gs);
        }
        displayArcadeMenu(gs);
        break;
    case GAME_START:
        if (_isCreated == false || _status != GAME_START) {
            _isCreated = true;
            _status = GAME_START;
            setGameMenuAssets(gs);
        }
        displayGameMenu(gs);
        break;
    case IN_GAME:
        if (_isCreated == false || _status != IN_GAME) {
            _isCreated = true;
            _status = IN_GAME;
            setGameAssets(gs);
        }
        // _map.clear();
        // for (size_t i = 0; i < gs.getGameArray().size(); i++) {
        //     _map += gs.getGameArray()[i];
        // }
        displayGame(gs);
        break;
    case GAME_END:
        if (_isCreated == false || _status != GAME_END) {
            _isCreated = true;
            _status = GAME_END;
            setGameOverMenuAssets();
        }
        displayGameOverMenu(gs);
        break;
    default:
        break;
    }
}

arcade::SFML::~SFML()
{
}

extern "C"
{
    arcade::IGraph *instance()
    {
        return new arcade::SFML();
    }
}
